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

class GridNode
{
private:
    string Name;
    
    int BACK_LOG = 5;
    
    BasicServer NodeServer;
    GridConnection NodeAdmin;

    unordered_map<int, GridConnection> Members;
    unordered_map<int, GridConnection> Clients;
    vector<GridConnection> QueuedConnections;

    vector<unique_ptr<IJob>> LocalJobs;
    unordered_map<int, vector<unique_ptr<IJob>>> MemberJobs;

    vector<shared_ptr<IParser>> CollectiveParsers;
    unordered_map<string, shared_ptr<ISerializer>> CollectiveSerializers;

    vector<unique_ptr<IHandler>> Handlers;

    void Init();

public:
    thread ConnectionListener;

    GridNode() { Name = ""; };
    GridNode(string Name);

    void AddCollectiveParser(shared_ptr<IParser>& Parser);
    void AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer);
    void AddHandler(unique_ptr<IHandler>& Handler);

    int Setup(string Host, string Port);
    void ConnectionListenerFunc();

    int ConnectToNode(string Host, string Port, bool IsWorker);

    GridConnection& GetConnection(int ConenctionID);
    void GetMemberIDs(vector<int>& OutIDs);
    void GetClientIDs(vector<int>& OutIDs);
};