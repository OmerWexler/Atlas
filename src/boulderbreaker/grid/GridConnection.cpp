#include "GridConnection.h"
#include "BasicConnection.h"
#include "ICallback.h"

#include "RequestBestNodeSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobPolicySerializer.h"

#include "RequestBestNodeParser.h"
#include "CancelJobParser.h"
#include "SendJobPolicyParser.h"

#include "IJob.h"

GridConnection::GridConnection()
{
    this->Callbacks = unordered_map<string, ICallback<GridConnection>*>();
    this->PeerJobPolicy = false;

    this->Connection = BasicConnection();
}

GridConnection::GridConnection(BasicConnection& Connection)
{
    this->Callbacks = unordered_map<string, ICallback<GridConnection>*>();
    this->PeerJobPolicy = false;

    this->Connection = Connection;
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
    Callbacks[Callback->GetMessageType()] = Callback;
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

int GridConnection::Connect(string Host, string Port)
{
    return Connection.Connect(Host, Port);
}