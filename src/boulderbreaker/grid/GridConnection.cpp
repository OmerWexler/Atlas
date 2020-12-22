#include <memory>

#include "GridConnection.h"
#include "BasicConnection.h"
#include "ICallback.h"
#include "IPCSearchPolicy.h"

#include "IParser.h"
#include "ISerializer.h"
#include "IMessage.h"

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

void GridConnection::AddDefaultInterfaces()
{

}


void GridConnection::AddCustomSerializer(ISerializer* Serializer)
{
    Connection.AddSerializer(Serializer);
}

void GridConnection::AddCustomCallback(ICallback<GridConnection>* Callback)
{
    Callbacks[Callback->GetMessageType()] = Callback;
}

int GridConnection::Connect(string Host, string Port)
{
    return Connection.Connect(Host, Port);
}

void GridConnection::SendJobPolicy(bool AcceptJobs)
{
    
}

int GridConnection::CancelJob(const IJob& Job)
{
    return -1;
}

int GridConnection::SendJob(const IJob& Job, IPCSearchPolicy ComparePolicy)
{
    return -1;
}

int GridConnection::SearchJobCandidate(IPCSearchPolicy ComparePolicy)
{
    return -1;
}

int GridConnection::SuggestJobCandidate(const PCPerformance& Performance, IPCSearchPolicy ComparePolicy)
{
    return -1;
}

int GridConnection::SendMessage(const unique_ptr<IMessage>& Msg)
{
    return -1;
}

bool GridConnection::GetPeerJobPolicy()
{
    return false;
}

int GridConnection::Disconnect()
{
    return -1;
}
