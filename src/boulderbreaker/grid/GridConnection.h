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

public:
    GridConnection(); 
    GridConnection(BasicConnection& Connection);

    int Connect(string Host, string Port, bool IsWorker);

    int SendMessage(const unique_ptr<IMessage>& Msg);

    int RequestBestNode(int Range, PCPerformance& MinimumAcceptablePerformace);
    int SendBestNode(const PCPerformance& Performance);

    int SendJob(IJob* Job, vector<Argument>& Input);
    int SendJobOutput(IJob* Job, vector<Argument>& Output);
    int CancelJob(IJob* Job);

    int Disconnect();
};