#pragma once

#include <unordered_map>

#include "PCPerformance.h"
#include "IJob.h"

#include "BasicConnection.h"
#include "ICallback.h"

#include "IParser.h"
#include "ISerializer.h"
#include "IMessage.h"

class GridConnection
{
private:
    BasicConnection Connection;
    unordered_map<string, ICallback<GridConnection>*> Callbacks;
    bool PeerJobPolicy;

    void AddDefaultInterfaces();
public:
    GridConnection(); 
    GridConnection(BasicConnection& Connection);

    void AddCustomParser(IParser* Parser);
    void AddCustomSerializer(ISerializer* Serializer);
    void AddCustomCallback(ICallback<GridConnection>* Callback);

    int Connect(string Host, string Port);

    void SendJobPolicy(bool AcceptJobs);
    int CancelJob(const IJob& Job);
    int SendJob(const IJob& Job);

    int RequestBestNode(int Range, PCPerformance MinimumAcceptablePerformace, PCPerformance& BestNode);
    int SendBestNode(const PCPerformance& Performance);

    int SendMessage(const unique_ptr<IMessage>& Msg);

    bool GetPeerJobPolicy();

    int Disconnect();
};