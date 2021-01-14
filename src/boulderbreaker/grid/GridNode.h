#pragma once

#include <unordered_map>
#include <vector>

#include "BasicServer.h"
#include "GridConnection.h"
#include "IHandler.h"
#include "IParser.h"
#include "ISerializer.h"

class GridNode
{
private:
    string Name;
    
    BasicServer NodeServer;
    GridConnection NodeAdmin;

    unordered_map<int, GridConnection> Members;
    unordered_map<int, GridConnection> Clients;
    vector<GridConnection> QueuedConnections;

    vector<IJob*> LocalJobs;
    unordered_map<int, vector<IJob*>> MemberJobs;

    vector<IParser*> CollectiveParsers;
    unordered_map<string, ISerializer*> CollectiveSerializers;

    vector<IHandler*> Handlers;

    void Init();

public:
    GridNode(string Name);

    void AddCollectiveParser(IParser* Parser);
    void AddCollectiveSerializer(ISerializer* Serializer);
    void AddHandler(IHandler* Handler);

    int Setup(string Host, string Port);

    int AccpetNodeConnection();
    int ConnectToNode(string Host, string Port, bool IsWorker);

    int SendJob(const IJob* Job, int Range, PCPerformance& MinimumAcceptablePerformance);

    GridConnection& GetConnection(int ConenctionID);
    void GetConnectionIDs(vector<int>& OutIDs);
};