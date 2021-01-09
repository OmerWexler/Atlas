#include "GridConnection.h"
#include "BasicConnection.h"
#include "ICallback.h"

#include "RequestBestNodeSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobPolicySerializer.h"
#include "SendJobSerializer.h"

#include "RequestBestNodeParser.h"
#include "CancelJobParser.h"
#include "SendJobPolicyParser.h"
#include "SendJobParser.h"

#include "RequestBestNodeMessage.h"
#include "CancelJobMessage.h"
#include "SendJobPolicyMessage.h"
#include "SendJobMessage.h"

#include "IJob.h"

GridConnection::GridConnection()
{
    this->Callbacks = unordered_map<string, ICallback<GridConnection>*>();
    this->PeerJobPolicy = false;

    this->Connection = BasicConnection();
    this->AddDefaultInterfaces();
}

GridConnection::GridConnection(BasicConnection& Connection)
{
    this->Callbacks = unordered_map<string, ICallback<GridConnection>*>();
    this->PeerJobPolicy = false;

    this->Connection = Connection;
    this->AddDefaultInterfaces();
}

void GridConnection::AddDefaultInterfaces()
{
    AddCustomSerializer((ISerializer*) new CancelJobSerializer());
    AddCustomSerializer((ISerializer*) new RequestBestNodeSerializer());
    AddCustomSerializer((ISerializer*) new SendJobPolicySerializer());

    AddCustomParser((IParser*) new CancelJobParser());
    AddCustomParser((IParser*) new RequestBestNodeParser());
    AddCustomParser((IParser*) new SendJobPolicyParser());
}

void GridConnection::AddCustomParser(IParser* Parser)
{
    Connection.AddParser(Parser);
}

void GridConnection::AddCustomSerializer(ISerializer* Serializer)
{
    Connection.AddSerializer(Serializer);
}

void GridConnection::AddCustomCallback(ICallback<GridConnection>* Callback)
{
    if (Callbacks.find(Callback->GetMessageType()) != Callbacks.end())
    {
        return;
    }

    Callbacks[Callback->GetMessageType()] = Callback;
}

int GridConnection::SendMessage(const unique_ptr<IMessage>& Msg)
{
    return Connection.Send(Msg);
}

int GridConnection::SendJobPolicy(bool AcceptJobs)
{
    return Connection.Send(unique_ptr<IMessage>((IMessage*) new SendJobPolicyMessage(AcceptJobs)));
}

int GridConnection::CancelJob(const IJob* Job)
{
    return Connection.Send(unique_ptr<IMessage>((IMessage*) new CancelJobMessage(Job->GetUniqueDescriptor())));
}

int GridConnection::SendJob(const IJob* Job)
{
    return 0;
}

int GridConnection::RequestBestNode(int Range, PCPerformance MinimumAcceptablePerformace)
{
    return 0;
}

int GridConnection::SendBestNode(const PCPerformance& Performance)
{
    return 0;
}

bool GridConnection::GetPeerJobPolicy()
{
    return false;
}

int GridConnection::Disconnect()
{
    return 0;
}