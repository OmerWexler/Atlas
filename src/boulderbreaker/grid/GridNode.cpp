#pragma once

#include "GridNode.h"
#include "BasicServer.h"

#include "SendJobPolicySerializer.h"
#include "RequestBestNodeSerializer.h"
#include "SendBestNodeSerializer.h"
#include "SendJobSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobOutputSerializer.h"

#include "SendJobPolicyParser.h"
#include "RequestBestNodeParser.h"
#include "SendBestNodeParser.h"
#include "SendJobParser.h"
#include "CancelJobParser.h"
#include "SendJobOutputParser.h"

#include "SendJobPolicyMessage.h"
#include "RequestBestNodeMessage.h"
#include "SendBestNodeMessage.h"
#include "SendJobMessage.h"
#include "CancelJobMessage.h"
#include "SendJobOutputMessage.h"

#include "JobCore.h"

#include "Utils.h"
#include "Logger.h"

GridNode::GridNode()
{
    this->Name = "";
    this->NodeServer = move(BasicServer("", false));
    Init();
}

GridNode::GridNode(string Name)
{
    this->Name = Name;
    this->NodeServer = move(BasicServer("BasicServer - " + Name, false));
    Init();
}

void GridNode::SetName(string Name)
{
    this->Name = Name;
    this->NodeServer.SetName("BasicServer - " + Name);
}

void GridNode::Init()
{
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobPolicyParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW RequestBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW CancelJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobOutputParser()));

    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobPolicySerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW RequestBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW CancelJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobOutputSerializer()));

    AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) DBG_NEW JobCore()));
}

void GridNode::AddConnectionToMap(unordered_map<int, GridConnection>& Map, string Type, vector<int>& Slots, GridConnection& Connection)
{
    int NewID = 0;

    if (Slots.size() > 0)
    {   
        NewID = Slots[Slots.size() - 1];
        Slots.erase(Slots.end() - 1);
    }
    else
    {
        NewID = (int) Map.size();
    }

    string NewName = this->Name + "::" + Type + to_string(NewID);
    Connection.SetName(NewName);
    Map[NewID] = move(Connection);

    Singleton<Logger>::GetInstance().Info(Name + " registered - " + NewName);
}

void GridNode::AddCollectiveParser(shared_ptr<IParser>& Parser)
{
    NodeServer.AddParser(Parser);

    for(int i = 0; i < CollectiveParsers.size(); i++)
    {
        if (CollectiveParsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    CollectiveParsers.push_back(shared_ptr<IParser>(Parser));
}

void GridNode::AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer)
{
    NodeServer.AddSerializer(shared_ptr<ISerializer>(Serializer));

    if (CollectiveSerializers.find(Serializer->GetType()) == CollectiveSerializers.end())
    {
        CollectiveSerializers[Serializer->GetType()] = Serializer;
    }
}

void GridNode::AddFunctionCore(unique_ptr<IFunctionCore>& Core)
{
    FunctionCores.push_back(unique_ptr<IFunctionCore>(Core.release()));
}

int GridNode::Setup(string Host, string Port)
{
    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
        return Result;

    Result = -1;
    while (Result != 0)
    {
        Result = NodeServer.Listen(BACK_LOG);
        Utils::CPSleep(1);
    }

    ConnectionListener = SmartThread(Name + " - ConnectionListener", 1.f, &GridNode::ConnectionListenerFunc, this);
    MemberManager = SmartThread(Name + " - MemberMananger", 1.f, &GridNode::MemberListenerFunc, this);
    ClientManager = SmartThread(Name + " - ClientMananger", 1.f, &GridNode::ClientListenerFunc, this);
    return 0;
}

void GridNode::ConnectionListenerFunc()
{
    BasicConnection NewConnection{};
    int Result = NodeServer.AcceptConnection("", NewConnection);
    if (Result != 0)
        return;

    GridConnection NewGridConnection = move(GridConnection(NewConnection));

    unique_ptr<IMessage> Msg;
    NewGridConnection.SetName("Unnamed");
    Result = -1;
    while (Result <= 0)
        Result = NewGridConnection.RecvMessage(Msg);

    if (Msg->GetType() == SendJobPolicyMessage::TYPE)
    {
        if (((SendJobPolicyMessage*) Msg.get())->GetPolicy())
        {
            AddConnectionToMap(Members, "Member", AvailableMemberSlots, NewGridConnection);
        }
        else
        {
            AddConnectionToMap(Clients, "Client", AvailableClientSlots, NewGridConnection);
        }
    }
}

void GridNode::MemberListenerFunc()
{
    IterateOnConnectionMap(Members, AvailableMemberSlots);
}

void GridNode::ClientListenerFunc()
{
    IterateOnConnectionMap(Clients, AvailableClientSlots);
}

void GridNode::IterateOnConnectionMap(unordered_map<int, GridConnection>& Map, vector<int>& Slots)
{
    unique_ptr<IMessage> Message;
    unordered_map<int, GridConnection>::iterator Iterator = Map.begin();

    while (Iterator != Map.end())
    {   
        if (!Iterator->second.IsConnected())
        {
            Slots.push_back(Iterator->first);
            Iterator = Map.erase(Iterator);
            continue;
        }

        int Result = Iterator->second.RecvMessage(Message);
        if (Result < 0)
        {
            Iterator++;
            continue;
        }
        
        for (unique_ptr<IFunctionCore>& Core: FunctionCores)
        {
            if (Core->IsMessageRelated(Message))
            {
                Core->QueueMessage(Message, Iterator->second);
            }
        }
        Iterator++;
    }
}

int GridNode::ConnectToNode(string Host, string Port, bool IsWorker)
{
    GridConnection NewConnection{"Connection To - " + Name};
    NewConnection.CopyCommInterfaces(CollectiveParsers, CollectiveSerializers);
    
    int Result = NewConnection.Connect(Host, Port, IsWorker);
    if (Result != 0)
    {
        return Result;
    }

    NodeAdmin = move(NewConnection);
    return 0;
}

GridConnection& GridNode::GetMember(int MemberID)
{
    return Members[MemberID];
}

vector<int> GridNode::GetMemberIDs()
{
    vector<int> IDs;
    for (auto& Member: Members)
    {
        IDs.push_back(Member.first);
    }
    return IDs;
}

GridConnection& GridNode::GetClient(int ClientID)
{
    return Clients[ClientID];
}
    
vector<int> GridNode::GetClientIDs()
{
    vector<int> IDs;
    for (auto& Client: Clients)
    {
        IDs.push_back(Client.first);
    }
    return IDs;
}

void GridNode::Stop()
{
    ConnectionListener.Stop();
    MemberManager.Stop();
    ClientManager.Stop();
}

GridNode::~GridNode()
{
    Stop();
}