#pragma once

#include <unordered_map>
#include <vector>

#include "BasicServer.h"
#include "GridConnection.h"
#include "ICallback.h"
#include "IParser.h"
#include "ISerializer.h"

class GridNode
{
private:
    string NodeName;
    bool AcceptJobs;
    
    BasicServer NodeServer;
    unordered_map<int, GridConnection> Connections;
    
    unordered_map<string, IParser*> CollectiveParser;
    unordered_map<string, ISerializer*> CollectiveSerializers;
    unordered_map<string, ICallback<GridConnection>*> CollectiveCallbacks;

public:
    GridNode(string Name);

    void AddCollectiveCustomParser(IParser* Parser);
    void AddCollectiveCustomSerializer(ISerializer* Serializer);
    void AddCollectiveCustomCallback(ICallback<GridConnection>* Callback);

    int Setup(string Host, string Port);
    int AccpetNodeConnection();
    int ConnectToNode(string Host, string Port);

    void SetJobPolicy(bool AcceptJobs);
    bool GetJobPolicy();
    int SendJob(const IJob* Job, int Range, PCPerformance& MinimumAcceptablePerformance);

    GridConnection GetConnection(int ConenctionID);
    void GetConnectionIDs(vector<int>& OutIDs);
};