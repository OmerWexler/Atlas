#pragma once

#include <unordered_map>
#include <vector>
#include <thread> 
#include <memory> 

#include "BasicServer.h"
#include "GridConnection.h"
#include "IHandler.h"
#include "IParser.h"
#include "ISerializer.h"
#include "Logger.h"

class GridNode
{
private:
    int BACK_LOG = 5;
    
    string Name;
    BasicServer NodeServer;
    GridConnection NodeAdmin;

    thread ConnectionListener;
    thread QueueManager;
    thread MemberManager;
    thread ClientManager;
    
    vector<unique_ptr<IJob>> LocalJobs;
    unordered_map<int, vector<unique_ptr<IJob>>> MemberJobs;

    vector<shared_ptr<IParser>> CollectiveParsers;
    unordered_map<string, shared_ptr<ISerializer>> CollectiveSerializers;

    vector<unique_ptr<IHandler>> Handlers;

    unordered_map<int, GridConnection> Members;
    vector<int> AvailableMemberSlots;
    
    unordered_map<int, GridConnection> Clients;
    vector<int> AvailableClientSlots;

    vector<GridConnection> QueuedConnections;

    bool ThreadsAlive = true;
    
    void Init();
    string CreateMemberName();
    string CreateClientName();

    void PopFromQueueTo(unordered_map<int, GridConnection>& To, string Name, int QueueID, vector<int>& Slots);

public:
    GridNode();
    GridNode(string Name);

    void SetName(string Name);

    void RegisterMemberFromQueue(int QueueID);
    void RegisterClientFromQueue(int QueueID);

    void AddCollectiveParser(shared_ptr<IParser>& Parser);
    void AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer);
    void AddHandler(unique_ptr<IHandler>& Handler);

    int Setup(string Host, string Port);
    void ConnectionListenerFunc();
    void QueueManagerFunc();

    void IterateOnConnectionMap(unordered_map<int, GridConnection>& Map, vector<int>& Slots);
    void MemberManagerFunc();
    void ClientManagerFunc();

    int ConnectToNode(string Host, string Port, bool IsWorker);

    int CancelJob(IJob* Job);

    GridConnection& GetAdmin() { return NodeAdmin; };

    GridConnection& GetMember(int MemberID);
    void GetMemberIDs(vector<int>& OutIDs);

    GridConnection& GetClient(int ClientID);
    void GetClientIDs(vector<int>& OutIDs);

    GridConnection& GetQueuedConnection(int ClientID);
    void GetQueuedConnectionIDs(vector<int>& OutIDs);

    void Stop();
    ~GridNode();
};