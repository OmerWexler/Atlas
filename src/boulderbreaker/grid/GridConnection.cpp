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

void GridConnection::AddCustomSerializer(ISerializer* Serializer)
{
    Connection.AddParser(ISerializer);
}

void GridConnection::AddCustomCallback(ICallback<GridConnection>* Callback)
{

}

int GridConnection::Connect(string Host, string Port)
{

}

void GridConnection::StartAcceptingMessages()
{

}

void GridConnection::SendJobPolicy(bool AcceptJobs)
{

}

int GridConnection::CancelJob(const IJob& Job)
{

}

int GridConnection::SendJob(const IJob& Job, IPCSearchPolicy ComparePolicy)
{

}

int GridConnection::SearchJobCandidate(IPCSearchPolicy ComparePolicy)
{

}

int GridConnection::SuggestJobCandidate(const PCPerformance& Performance, IPCSearchPolicy ComparePolicy)
{

}

int GridConnection::SendMessage(const unique_ptr<IMessage>& Msg)
{

}

bool GridConnection::GetPeerJobPolicy()
{

}

int GridConnection::Disconnect()
{

}
