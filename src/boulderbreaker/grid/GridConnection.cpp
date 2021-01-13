#include "GridConnection.h"
#include "BasicConnection.h"
#include "ICallback.h"

#include "RequestBestNodeSerializer.h"
#include "SendBestNodeSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobPolicySerializer.h"
#include "SendJobSerializer.h"
#include "SendJobOutputSerializer.h"

#include "RequestBestNodeParser.h"
#include "SendBestNodeParser.h"
#include "CancelJobParser.h"
#include "SendJobPolicyParser.h"
#include "SendJobParser.h"
#include "SendJobOutputParser.h"

#include "RequestBestNodeMessage.h"
#include "SendBestNodeMessage.h"
#include "CancelJobMessage.h"
#include "SendJobPolicyMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"

#include "IJob.h"

GridConnection::GridConnection()
{
    this->Connection = BasicConnection();
}

GridConnection::GridConnection(BasicConnection& Connection)
{
    this->Connection = Connection;
}

int GridConnection::Connect(string Host, string Port, bool IsWorker)
{
    int Result = Connection.Connect(Host, Port); 
    if (Result == 0)
    {
        Connection.Send(unique_ptr<IMessage>((IMessage*) new SendJobPolicyMessage(IsWorker)));
    }

    return Result;
}

int GridConnection::SendMessage(const unique_ptr<IMessage>& Msg)
{
    return Connection.Send(Msg);
}

int GridConnection::SendJob(IJob* Job, vector<Argument>& Input)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new SendJobMessage(Job, Input)));
}

int GridConnection::SendJobOutput(IJob* Job, vector<Argument>& Output)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new SendJobOutputMessage(Job->GetUniqueDescriptor(), Output)));
}

int GridConnection::CancelJob(IJob* Job)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new CancelJobMessage(Job->GetUniqueDescriptor())));
}

int GridConnection::RequestBestNode(int Range, PCPerformance& MinimumAcceptablePerformace)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new RequestBestNodeMessage(Range, MinimumAcceptablePerformace)));
}

int GridConnection::SendBestNode(const PCPerformance& Performance)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new SendBestNodeMessage(Performance)));
}

int GridConnection::Disconnect()
{
    return Connection.Disconnect();
}