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
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobPolicyParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new RequestBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new CancelJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobOutputParser()));

    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobPolicySerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new RequestBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new CancelJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobOutputSerializer()));

    AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) new JobCore()));
}

void GridNode::PopFromQueueTo(unordered_map<int, GridConnection>& To, string Type, int QueueID, vector<int>& Slots)
{
    GridConnection NewMember = move(QueuedConnections[QueueID]);
    QueuedConnections.erase(QueuedConnections.begin() + QueueID);

    int NewID = 0;

    if (Slots.size() > 0)
    {   
        NewID = Slots[Slots.size() - 1];
        Slots.erase(Slots.end() - 1);
    }
    else
    {
        NewID = (int) Members.size();
    }

    string NewName = this->Name + "::" + Type + to_string(NewID);
    NewMember.SetName(NewName);
    To[NewID] = move(NewMember);

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
    if (CollectiveSerializers.find(Serializer->GetType()) == CollectiveSerializers.end())
    {
        CollectiveSerializers[Serializer->GetType()] = Serializer;
    }

    NodeServer.AddSerializer(shared_ptr<ISerializer>(Serializer));
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

    ConnectionListener = thread(&GridNode::ConnectionListenerFunc, this);
    QueueManager = thread(&GridNode::QueueManagerFunc, this);
    MemberManager = thread(&GridNode::MemberManagerFunc, this);
    ClientManager = thread(&GridNode::ClientManagerFunc, this);
    return 0;
}

void GridNode::ConnectionListenerFunc()
{
    int Result = -1;
    while (Result != 0 && ThreadsAlive)
    {
        Result = NodeServer.Listen(BACK_LOG);
        Utils::CPSleep(1);
    }

    while (ThreadsAlive)
    {
        BasicConnection NewConnection{}; 
        int Result = NodeServer.AcceptConnection("", NewConnection);
        GridConnection NewGridConnection = GridConnection(NewConnection);

        unique_ptr<IMessage> Msg;
        NewGridConnection.RecvMessage(Msg);
        if (Msg->GetType() == SendJobPolicyMessage::TYPE)
        {

        }

        // if (Result == 0)
        //     QueuedConnections.push_back();
        
        Utils::CPSleep(1);
    }
}

void GridNode::QueueManagerFunc()
{
    unique_ptr<IMessage> Message;
    int Result;
    while (ThreadsAlive)
    {
        for (int i = 0; i < QueuedConnections.size(); i++)
        {
            Result = QueuedConnections[i].RecvMessage(Message);
            if (Result != 0)
            {
                if (!QueuedConnections[i].IsConnected())
                {
                    QueuedConnections.erase(QueuedConnections.begin() + i);
                    continue;
                }
            }
            
            for (unique_ptr<IFunctionCore>& Core: FunctionCores)
            {
                if (Core->IsMessageRelated(Message))
                {
                    Core->AddMessage(Message, QueuedConnections[i]);
                }
            }
        }

        Utils::CPSleep(1);
    }
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
        if (Result != 0)
        {
            Iterator++;
            continue;
        }
        
        for (unique_ptr<IFunctionCore>& Core: FunctionCores)
        {
            if (Core->IsMessageRelated(Message))
            {
                Core->AddMessage(Message, Iterator->second);
            }
        }
        Iterator++;
    }
}

void GridNode::MemberManagerFunc()
{
    while (ThreadsAlive)
    {
        if (Members.size() > 0)
            IterateOnConnectionMap(Members, AvailableMemberSlots);
        Utils::CPSleep(1);
    }
}

void GridNode::ClientManagerFunc()
{
    unique_ptr<IMessage> Message;
    while (ThreadsAlive)
    {
        if (Clients.size() > 0)
            IterateOnConnectionMap(Clients, AvailableClientSlots);        
        Utils::CPSleep(1);
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

void GridNode::GetMemberIDs(vector<int>& OutIDs)
{
    OutIDs.clear();
    for (auto& Member: Members)
    {
        OutIDs.push_back(Member.first);
    }
}

GridConnection& GridNode::GetClient(int ClientID)
{
    return Clients[ClientID];
}
    
void GridNode::GetClientIDs(vector<int>& OutIDs)
{
    OutIDs.clear();
    for (auto& Client: Clients)
    {
        OutIDs.push_back(Client.first);
    }
}

void GridNode::Stop()
{
    ThreadsAlive = false;
    if (ConnectionListener.joinable())
        ConnectionListener.join();
    
    if (QueueManager.joinable())
        QueueManager.join();

    if (MemberManager.joinable())
        MemberManager.join();

    if (ClientManager.joinable())
        ClientManager.join();
}