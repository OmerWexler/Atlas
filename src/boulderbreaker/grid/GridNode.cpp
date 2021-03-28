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
#include "RejectNameSerializer.h"

#include "SendJobPolicyParser.h"
#include "RequestBestNodeParser.h"
#include "SendBestNodeParser.h"
#include "SendJobParser.h"
#include "CancelJobParser.h"
#include "SendJobOutputParser.h"
#include "SetNameParser.h"
#include "RejectNameParser.h"

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

#include "AtlasApp.h"
#include "MainFrame.h"

#undef SendMessage

GridNode::GridNode() : NodeServer("BasicServer - UnnamedNode", false)
{
    SetName("UnnamedNode", false);
    Init();
}

GridNode::GridNode(string Name) : NodeServer("BasicServer - " + Name, false)
{
    SetName(Name, false);
    Init();
}

void GridNode::SetName(string Name, bool BroadcastRequest)
{
    this->Name = Name;
    this->NodeServer.SetName("BasicServer - " + Name);

    if (BroadcastRequest)
    {
        BroadcastNameRequest(Name);
    }

    wxCommandEvent* event = new wxCommandEvent(EVT_NODE_NAME_CHANGED);
    wxQueueEvent(wxGetApp().GetMainFrame(), event);
}

void GridNode::BroadcastNameRequest(string Name)
{
    for (auto& Pair: Members)
    {
        if (Pair.second.IsConnected())
            Pair.second.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SetNameMessage(Name)));
    }
    for (auto& Pair: Clients)
    {
        if (Pair.second.IsConnected())
            Pair.second.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SetNameMessage(Name)));
    }

    if (NodeAdmin.IsConnected())
        NodeAdmin.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SetNameMessage(Name)));
}

void GridNode::Init()
{
    CollectiveParsers = vector<shared_ptr<IParser>>();
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobPolicyParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW RequestBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW CancelJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SendJobOutputParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SetNameParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW AcceptNameParser()));

    CollectiveSerializers = unordered_map<string, shared_ptr<ISerializer>>();
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobPolicySerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW RequestBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW CancelJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SendJobOutputSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SetNameSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW RejectNameSerializer()));

    FunctionCores = vector<unique_ptr<IFunctionCore>>();
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
    Singleton<Logger>::GetInstance().Info("Setting up at " + Host + ":" + Port);

    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
        return Result;

    Result = NodeServer.Listen(BACK_LOG);
    if (Result != 0)
        return Result;

    Singleton<Logger>::GetInstance().Info("Initiating threads...");
    ConnectionListener = SmartThread(Name + " - ConnectionListener", 0.02f, &GridNode::ConnectionListenerFunc, this);
    MemberManager = SmartThread(Name + " - MemberMananger", 0.02f, &GridNode::MemberListenerFunc, this);
    ClientManager = SmartThread(Name + " - ClientMananger", 0.02f, &GridNode::ClientListenerFunc, this);
    AdminManager = SmartThread(Name + " - AdminManager", 0.02f, &GridNode::ManageAdminFunc, this);
    Singleton<Logger>::GetInstance().Info("Threads running.");

    Singleton<Logger>::GetInstance().Info("Initiating cores...");
    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (ASyncFunctionCore* ACore = dynamic_cast<ASyncFunctionCore*>(Core.get()))
        {
            ACore->StartCore();
        }
    }
    Singleton<Logger>::GetInstance().Info("Cores ready.");

    wxCommandEvent* event = new wxCommandEvent(EVT_LISTEN_ADDRESS_CHANGED);
    event->SetString(wxString(Host + ":" + Port));
    wxQueueEvent(wxGetApp().GetMainFrame(), event);
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
    
    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (Core->IsMessageRelated(Message))
        {
            Core->QueueMessage(Message, Connection);
            return 0;
        }
    }

    return -1;
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
    wxCommandEvent* event = new wxCommandEvent(EVT_NODE_ADMIN_NAME_CHANGED);
    event->SetString(wxString("Unnamed (" + NodeAdmin.GetHost() + ":" + NodeAdmin.GetPort() + ")"));
    wxQueueEvent(wxGetApp().GetMainFrame(), event);
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

void GridNode::CloseServer()
{
    NodeServer.Close();
}

void GridNode::DisconnectFromAdmin()
{
    for (auto& Pair: Members)
    {
        if (Pair.second.IsConnected())
            Pair.second.Disconnect();
    }
}

void GridNode::DisconnectMembers()
{
    if (NodeAdmin.IsConnected())
        NodeAdmin.Disconnect();
}

void GridNode::StopPeriodics()
{
    if (ConnectionListener.GetIsRunning())
        ConnectionListener.Stop();
    
    if (MemberManager.GetIsRunning())
        MemberManager.Stop();
    
    if (ClientManager.GetIsRunning())
        ClientManager.Stop();
    
    if (AdminManager.GetIsRunning())
        AdminManager.Stop();

    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (ASyncFunctionCore* ACore = dynamic_cast<ASyncFunctionCore*>(Core.get()))
        {
            if (ACore->IsRunning())
                ACore->StopCore();
        }
    }
}

void GridNode::CloseNode()
{
    DisconnectFromAdmin();
    DisconnectMembers();
    CloseServer();
    StopPeriodics();
}

void GridNode::ReloadNode()
{
    CloseNode();
    NodeServer = move(BasicServer("BasicServer - UnnamedNode", false));

    SetName("UnnamedNode");
    Init();
}

GridNode::~GridNode()
{
    CloseNode();
}