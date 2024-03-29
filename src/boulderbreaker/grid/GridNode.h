#pragma once

#include <unordered_map>
#include <vector>
#include <thread> 
#include <memory> 

#include "BasicServer.h"
#include "GridConnection.h"
#include "IFunctionCore.h"
#include "IParser.h"
#include "ISerializer.h"
#include "Logger.h"
#include "SmartThread.h"
#include "Path.h"

#ifdef WIN32
    #include "WinPerformanceAnalyzer.h"
#endif

#define DEFAULT_NODE_CONNECTION_PORT "22000"

class GridNode
{
private:
    int BACK_LOG = 5;
    
    string Name;
    bool m_IsWorker = true;
    BasicServer NodeServer;
    GridConnection NodeAdmin;

    PCPerformance CurrentPerformance;
    PCPerformance GridTopPerformance;
    WinPerformanceAnalyzer PerformanceAnalyzer;
    Path TopPerformancePath;

    SmartThread ConnectionListener;
    SmartThread MemberManager;
    SmartThread ClientManager;
    SmartThread AdminManager;
    SmartThread ResourceReporter;

    vector<shared_ptr<IParser>> CollectiveParsers;
    unordered_map<string, shared_ptr<ISerializer>> CollectiveSerializers;

    vector<unique_ptr<IFunctionCore>> FunctionCores;
    
    vector<shared_ptr<IJob>> DispatchedJobs;
    vector<shared_ptr<IJob>> LocalJobs;

    unordered_map<int, GridConnection> Members;
    vector<int> AvailableMemberSlots;
    
    unordered_map<int, GridConnection> Clients;
    vector<int> AvailableClientSlots;

    void Init();
    void BroadcastNameRequest(string Name);

    string CreateMemberName();
    string CreateClientName();

    void AddConnectionToMap(unordered_map<int, GridConnection>& Map, string Type, vector<int>& Slots, GridConnection& Connection);

    void ConnectionListenerFunc();
    void MemberListenerFunc();
    void ClientListenerFunc();
    void IterateOnConnectionMap(unordered_map<int, GridConnection>& Map, vector<int>& Slots);
    
    void ManageAdminFunc();
    void ResourceManager();

    int RecvAndRerouteMessage(GridConnection& Connection);

public:
    GridNode();
    GridNode(string Name);

    void SetName(string Name, bool BroadcastRequest=true);
    string GetName() { return Name; };
    
    bool IsWorker() { return m_IsWorker; };

    void ReportNewTopPerformance(PCPerformance& NewPerformance, Path& NewNodePath);
    void RemoveJob(string JobDescriptor);
    int RouteMessageToSelf(unique_ptr<IMessage>& Message, GridConnection& Sender);

    void AddCollectiveParser(shared_ptr<IParser>& Parser);
    void AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer);
    void AddFunctionCore(unique_ptr<IFunctionCore>& Core);

    int Listen(string Host, string Port);
    void StartNode();

    int ConnectToNode(string Host, string Port, bool IsWorker);
    int SendFile(string Filepath, string DestPath, Path TargetNode);

    GridConnection& GetAdmin() { return NodeAdmin; };

    GridConnection& GetMember(int MemberID);
    unordered_map<int, GridConnection>::iterator GridNode::GetMembersBegin();
    unordered_map<int, GridConnection>::iterator GridNode::GetMembersEnd();

    GridConnection& GetClient(int ClientID);
    unordered_map<int, GridConnection>::iterator GridNode::GetClientsBegin();
    unordered_map<int, GridConnection>::iterator GridNode::GetClientsEnd();

    vector<shared_ptr<IJob>>::iterator GridNode::GetDispatchedJobsBegin() { return DispatchedJobs.begin(); };
    vector<shared_ptr<IJob>>::iterator GridNode::GetDispatchedJobsEnd() { return DispatchedJobs.end(); };

    void RegisterLocalJob(shared_ptr<IJob>& Job);
    void RemoveLocalJob(string Descriptor);
    vector<shared_ptr<IJob>>::iterator GridNode::GetLocalJobsBegin() { return LocalJobs.begin(); };
    vector<shared_ptr<IJob>>::iterator GridNode::GetLocalJobsEnd() { return LocalJobs.end(); };

    int SendJobToMembers(shared_ptr<IJob>& Job, vector<Argument>& Input);
    PCPerformance GetNodePerformance() { return CurrentPerformance; };
    PCPerformance GetGridTopPerformance() { return GridTopPerformance; };
    
    Path GetTopPerformancePath() { return TopPerformancePath; };

    void CloseServer();
    void DisconnectFromAdmin();
    void DisconnectMembers();
    void StopPeriodics();
    void StopAllDispatchedJobs();

    void CloseNode();

    ~GridNode();
};