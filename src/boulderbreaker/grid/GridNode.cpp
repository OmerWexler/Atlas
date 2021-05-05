#pragma once

#include "GridNode.h"
#include "BasicServer.h"

#include "SendJobPolicySerializer.h"
#include "DisconnectSerializer.h"
#include "SendNodePerformanceSerializer.h"
#include "SendJobSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobOutputSerializer.h"
#include "SetNameSerializer.h"
#include "RejectNameSerializer.h"

#include "SendJobPolicyParser.h"
#include "DisconnectParser.h"
#include "SendNodePerformanceParser.h"
#include "SendJobParser.h"
#include "CancelJobParser.h"
#include "SendJobOutputParser.h"
#include "SetNameParser.h"
#include "RejectNameParser.h"

#include "SendJobPolicyMessage.h"
#include "DisconnectMessage.h"
#include "SendNodePerformanceMessage.h"
#include "SendJobMessage.h"
#include "CancelJobMessage.h"
#include "SendJobOutputMessage.h"
#include "SetNameMessage.h"

#include "ASyncFunctionCore.h"

#include "JobCore.h"
#include "GeneralPurposeCore.h"
#include "ResourceCore.h"

#include "Utils.h"
#include "Logger.h"
#include "Path.h"

#include "AtlasApp.h"
#include "MainFrame.h"

#undef SendMessage

GridNode::GridNode() : NodeServer("BasicServer - UnnamedNode", false), PerformanceAnalyzer(10)
{
    SetName("UnnamedNode", false);
    Init();
}

GridNode::GridNode(string Name) : NodeServer("BasicServer - " + Name, false), PerformanceAnalyzer(10)
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

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_NODE_NAME_CHANGED);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
}

void GridNode::BroadcastNameRequest(string Name)
{
    for (auto& Pair: Members)
    {
        if (Pair.second.IsConnected())
            Pair.second.SendMessage(ATLS_CREATE_UNIQUE_MSG(SetNameMessage, Name));
    }
    for (auto& Pair: Clients)
    {
        if (Pair.second.IsConnected())
            Pair.second.SendMessage(ATLS_CREATE_UNIQUE_MSG(SetNameMessage, Name));
    }

    if (NodeAdmin.IsConnected())
        NodeAdmin.SendMessage(ATLS_CREATE_UNIQUE_MSG(SetNameMessage, Name));
}

void GridNode::Init()
{
    CollectiveParsers = vector<shared_ptr<IParser>>();
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SendJobPolicyParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(DisconnectParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SendNodePerformanceParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SendJobParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(CancelJobParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SendJobOutputParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SetNameParser));
    AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(RejectNameParser));

    CollectiveSerializers = unordered_map<string, shared_ptr<ISerializer>>();
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(SendJobPolicySerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(DisconnectSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(SendNodePerformanceSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(SendJobSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(CancelJobSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(SendJobOutputSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(SetNameSerializer));
    AddCollectiveSerializer(ATLS_CREATE_SHARED_SRLZR(RejectNameSerializer));

    FunctionCores = vector<unique_ptr<IFunctionCore>>();
    AddFunctionCore(ATLS_CREATE_UNIQUE_CORE(JobCore, Name + " - JobCore"));
    AddFunctionCore(ATLS_CREATE_UNIQUE_CORE(GeneralPurposeCore));
    AddFunctionCore(ATLS_CREATE_UNIQUE_CORE(ResourceCore));

    TopPerformancePath = Path();
    TopPerformancePath.AddToEnd(Name);
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
    Map[NewID].SendMessage(ATLS_CREATE_UNIQUE_MSG(SetNameMessage, Name));
    Singleton<Logger>::GetInstance().Info(Name + " registered new connection.");
}

void GridNode::AddCollectiveParser(shared_ptr<IParser>& Parser)
{
    NodeServer.AddParser(Parser);

    for(unsigned int i = 0; i < CollectiveParsers.size(); i++)
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

void GridNode::StartNode()
{
    Singleton<Logger>::GetInstance().Info("Initiating threads...");
    MemberManager = SmartThread(Name + " - MemberMananger", ST_UNLIMITED_RUNTIME, &GridNode::MemberListenerFunc, this);
    ClientManager = SmartThread(Name + " - ClientMananger", ST_UNLIMITED_RUNTIME, &GridNode::ClientListenerFunc, this);
    AdminManager = SmartThread(Name + " - AdminManager", ST_UNLIMITED_RUNTIME, &GridNode::ManageAdminFunc, this);
    ResourceReporter = SmartThread(Name + " - ResourceManager", 1.f, &GridNode::ResourceManager, this);
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
}

int GridNode::Listen(string Host, string Port)
{
    Singleton<Logger>::GetInstance().Info("Setting up at " + Host + ":" + Port);

    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
        return Result;

    Result = NodeServer.Listen(BACK_LOG);
    if (Result != 0)
        return Result;

    ConnectionListener = SmartThread(Name + " - ConnectionListener", 0.02f, &GridNode::ConnectionListenerFunc, this);

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_LISTEN_ADDRESS_CHANGED);
        event->SetString(wxString(Host + ":" + Port));
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
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

            if (wxGetApp().GetMainFrame())
            {
                wxCommandEvent* event = new wxCommandEvent(EVT_NODE_CONNECTIONS_CHANGED);
                wxQueueEvent(wxGetApp().GetMainFrame(), event);
            }
            
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
    
    return RouteMessageToSelf(Message, Connection);
}

void GridNode::ResourceManager()
{
    PCPerformance NodePerformance = PCPerformance();

    PerformanceAnalyzer.LoadDryStats(NodePerformance);
    PerformanceAnalyzer.MeasureCPUFrequency(NodePerformance);
    for (int i = 0; i < 5; i++)
    {
        PerformanceAnalyzer.MeasureCPULoad(NodePerformance);
        Utils::CPSleep(0.1f);
    }

    CurrentPerformance = NodePerformance;
    
    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_CURRENT_PERFORMANCE);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }

    if (Members.size() == 0) // No member to compare preformance to
    {
        TopPerformancePath = Path(Name);
        GridTopPerformance = NodePerformance;
        
        
        if (wxGetApp().GetMainFrame())
        {
            wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_TOP_PERFORMANCE);
            wxQueueEvent(wxGetApp().GetMainFrame(), event);
        }
    }

    if (NodeAdmin.IsConnected() && IsWorker && Members.size() == 0) // If is a grid leaf and connected to admin as worker
    {
        NodeAdmin.SendMessage(ATLS_CREATE_UNIQUE_MSG(SendNodePerformanceMessage, NodePerformance, Path(Name)));
    }
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

    if (NodeAdmin.IsConnected())
        NodeAdmin.Disconnect();
    
    NodeAdmin = move(NewConnection);
    
    this->IsWorker = IsWorker;

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_NODE_ADMIN_NAME_CHANGED);
        event->SetString(wxString("Unnamed (" + NodeAdmin.GetHost() + ":" + NodeAdmin.GetPort() + ")"));
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
    
    return 0;
}

int GridNode::SendJobToMembers(shared_ptr<IJob>& Job, vector<Argument>& Input)
{
    Job->SetPathToTarget(TopPerformancePath);
    unique_ptr<IMessage> Msg = ATLS_CREATE_UNIQUE_MSG(SendJobMessage, Job, Input, TopPerformancePath);
    DispatchedJobs.push_back(Job);
    
    int Result = RouteMessageToSelf(Msg, GridConnection());

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_JOB_LIST);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }

    return Result;
}

void GridNode::ReportNewTopPerformance(PCPerformance& NewPerformance, Path& NewNodePath)
{
    TopPerformancePath = NewNodePath;
    GridTopPerformance = NewPerformance;

    if (NodeAdmin.IsConnected())
    {
        Path NewPathFromAdmin = NewNodePath;
        NodeAdmin.SendMessage(ATLS_CREATE_UNIQUE_MSG(SendNodePerformanceMessage, NewPerformance, NewPathFromAdmin));
    }
}

void GridNode::RemoveJob(string JobDescriptor)
{
    auto& Iterator = DispatchedJobs.begin();
    while (Iterator != DispatchedJobs.end())
    {
        if (!Iterator->get() || Iterator->get()->GetUniqueDescriptor() == JobDescriptor)
        {
            Iterator = DispatchedJobs.erase(Iterator);
        }
        else
            Iterator++;
    }

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_JOB_LIST);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
}

void GridNode::RegisterLocalJob(shared_ptr<IJob>& Job) 
{ 
    LocalJobs.push_back(Job); 

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_LOCAL_JOB_LIST);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
}

void GridNode::RemoveLocalJob(string Descriptor)
{
    auto& Iterator = LocalJobs.begin();
    while (Iterator != LocalJobs.end())
    {
        if (Iterator->get()->GetUniqueDescriptor() == Descriptor)
        {
            Iterator = LocalJobs.erase(Iterator);
        }
        else
            Iterator++;
    }

    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_LOCAL_JOB_LIST);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
}

int GridNode::RouteMessageToSelf(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (Core->IsMessageRelated(Message))
        {
            Core->QueueMessage(Message, Sender);
            return 0;
        }
    }

    return -1;
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
    
    if (ResourceReporter.GetIsRunning())
        ResourceReporter.Stop();

    for (unique_ptr<IFunctionCore>& Core: FunctionCores)
    {
        if (ASyncFunctionCore* ACore = dynamic_cast<ASyncFunctionCore*>(Core.get()))
        {
            if (ACore->IsRunning())
                ACore->StopCore();
        }
    }
}

void GridNode::StopAllDispatchedJobs()
{
    for (auto& Job: DispatchedJobs)
    {
        RouteMessageToSelf(
            ATLS_CREATE_UNIQUE_MSG(CancelJobMessage, Job->GetUniqueDescriptor(), Job->GetPathToTarget().GetStrPath()),
            GridConnection()
        );
    }

    DispatchedJobs.clear();
}

void GridNode::CloseNode()
{
    StopAllDispatchedJobs();
    DisconnectFromAdmin();
    DisconnectMembers();
    CloseServer();
    StopPeriodics();
}

GridNode::~GridNode()
{
    CloseNode();
}