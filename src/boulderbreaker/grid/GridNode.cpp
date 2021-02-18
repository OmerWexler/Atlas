#pragma once

#include "GridNode.h"
#include "BasicServer.h"

#include "SendJobPolicySerializer.h"
#include "RequestBestNodeSerializer.h"
#include "SendBestNodeSerializer.h"
#include "SendJobSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobOutputSerializer.h"
#include "SetNameSerializer.h"
#include "AcceptNameSerializer.h"

#include "SendJobPolicyParser.h"
#include "RequestBestNodeParser.h"
#include "SendBestNodeParser.h"
#include "SendJobParser.h"
#include "CancelJobParser.h"
#include "SendJobOutputParser.h"
#include "SetNameParser.h"
#include "AcceptNameParser.h"

#include "SendJobPolicyMessage.h"
#include "RequestBestNodeMessage.h"
#include "SendBestNodeMessage.h"
#include "SendJobMessage.h"
#include "CancelJobMessage.h"
#include "SendJobOutputMessage.h"
#include "SetNameMessage.h"

#include "ASyncFunctionCore.h"
#include "JobCore.h"
#include "GeneralPurposeCore.h"

#include "Utils.h"
#include "Logger.h"

GridNode::GridNode()
{
    this->Name = "";
    this->NodeServer = move(BasicServer("", false));
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
    Init();
}

void GridNode::Init()
{
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobPolicyParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW RequestBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW CancelJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobOutputParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SetNameParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW AcceptNameParser()));

    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobPolicySerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW RequestBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW CancelJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobOutputSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SetNameSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW AcceptNameSerializer()));

    AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) DBG_NEW JobCore(Name + " - JobCore")));
    AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) DBG_NEW GeneralPurposeCore()));
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

    Map[NewID] = move(Connection);
    Map[NewID].SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SetNameMessage(Name)));

    Singleton<Logger>::GetInstance().Info(Name + " registered new connection.");
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
    for (unique_ptr<IFunctionCore>& ExistCore: FunctionCores)
    {
        if (ExistCore->GetType() == Core->GetType())
        {
            return;
        }
    }

    FunctionCores.push_back(unique_ptr<IFunctionCore>(Core.release()));
}

int GridNode::Setup(string Host, string Port)
{
    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
        return Result;

    Result = NodeServer.Listen(BACK_LOG);
    if (Result != 0)
        return Result;

    ConnectionListener = SmartThread(Name + " - ConnectionListener", 1.f, &GridNode::ConnectionListenerFunc, this);
    MemberManager = SmartThread(Name + " - MemberMananger", 1.f, &GridNode::MemberListenerFunc, this);
    ClientManager = SmartThread(Name + " - ClientMananger", 1.f, &GridNode::ClientListenerFunc, this);
    AdminManager = SmartThread(Name + " - AdminManager", 1.f, &GridNode::ManageAdminFunc, this);

    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        ASyncFunctionCore* ACore = dynamic_cast<ASyncFunctionCore*>(Core.get());

        if (ACore != nullptr)
        {
            ACore->StartCore();
        }
    }

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
    unordered_map<int, GridConnection>::iterator Iterator = Map.begin();
    
    while (Iterator != Map.end())
    {   
        if (!Iterator->second.IsConnected())
        {
            Slots.push_back(Iterator->first);
            Iterator = Map.erase(Iterator);
            continue;
        }

        int Result = RecvAndRerouteMessage(Iterator->second);
        Iterator++;
    }
}

void GridNode::ManageAdminFunc()
{
    if (NodeAdmin.IsConnected())
    {
        RecvAndRerouteMessage(NodeAdmin);
    }
}


int GridNode::RecvAndRerouteMessage(GridConnection& Connection)
{
    unique_ptr<IMessage> Message;
    int Result = Connection.RecvMessage(Message);
    if (Result < 0)
    {
        return Result;
    }
    
    int NumOfMatches = 0;
    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (Core->IsMessageRelated(Message))
        {
            Core->QueueMessage(Message, Connection);
            NumOfMatches++;
        }
    }

    return NumOfMatches;
}

int GridNode::ConnectToNode(string Host, string Port, bool IsWorker)
{
    GridConnection NewConnection = move(GridConnection());
    NewConnection.CopyCommInterfaces(CollectiveParsers, CollectiveSerializers);
    
    int Result = NewConnection.Connect(Host, Port, IsWorker, Name);
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

unordered_map<int, GridConnection>::iterator GridNode::GetMembersBegin()
{
    return Members.begin();
}

unordered_map<int, GridConnection>::iterator GridNode::GetMembersEnd()
{
    return Members.end();
}

GridConnection& GridNode::GetClient(int ClientID)
{
    return Clients[ClientID];
}
 
unordered_map<int, GridConnection>::iterator GridNode::GetClientsBegin()
{
    return Clients.begin();
}
 
unordered_map<int, GridConnection>::iterator GridNode::GetClientsEnd()
{
    return Clients.end();
}

void GridNode::Stop()
{
    ConnectionListener.Stop();
    MemberManager.Stop();
    ClientManager.Stop();
    AdminManager.Stop();

    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        ASyncFunctionCore* ACore = dynamic_cast<ASyncFunctionCore*>(Core.get());

        if (ACore != nullptr)
        {
            ACore->StopCore();
        }
    }
}

GridNode::~GridNode()
{
    Stop();
}