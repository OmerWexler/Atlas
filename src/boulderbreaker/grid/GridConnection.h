#pragma once

#include <memory>
#include <unordered_map>

#include "BasicConnection.h"
#include "ICallback.h"
#include "IPCSearchPolicy.h"

#include "IParser.h"
#include "ISerializer.h"
#include "IMessage.h"

#include "IJob.h"

class GridConnection
{
private:
    BasicConnection Connection;
    unordered_map<string, ICallback<GridConnection>*> Callbacks;
    bool PeerJobPolicy;

    void AddDefault
public:
    GridConnection(); 
    GridConnection(BasicConnection Connection);

    void AddCustomParser(IParser* Parser);
    void AddCustomSerializer(ISerializer* Serializer);
    void AddCustomCallback(ICallback<GridConnection>* Callback);

    int Connect(string Host, string Port);
    void StartAcceptingMessages();

    void SendJobPolicy(bool AcceptJobs);

    int CancelJob(const IJob& Job);
    int SendJob(const IJob& Job, IPCSearchPolicy ComparePolicy);

    int SearchJobCandidate(IPCSearchPolicy ComparePolicy);
    int SuggestJobCandidate(const PCPerformance& Performance, IPCSearchPolicy ComparePolicy);

    int SendMessage(const unique_ptr<IMessage>& Msg);

    bool GetPeerJobPolicy();

    int Disconnect();
};