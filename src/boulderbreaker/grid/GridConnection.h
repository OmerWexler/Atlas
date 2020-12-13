#pragma once

#include <memory>

#include "BasicConnection.h"
#include "ICallback.h"
#include "IPCSearchPolicy.h"

#include "IParser.h"
#include "ISerializer.h"
#include "IMessage.h"

#include "IJob.h"

class GridConnection
{
public:
    GridConnection(); 
    GridConnection(BasicConnection Socket);

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