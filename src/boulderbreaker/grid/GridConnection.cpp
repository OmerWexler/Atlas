#include "GridConnection.h"
#include "BasicConnection.h"

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

using namespace std;
GridConnection::GridConnection()
{
    Name = "";
    this->Connection = move(BasicConnection(Name));
}

GridConnection::GridConnection(string Name)
{
    this->Name = Name;
    this->Connection = move(BasicConnection(Name));
}

GridConnection::GridConnection(BasicConnection& Connection)
{
    this->Name = Connection.GetName();
    this->Connection = move(Connection);
}

GridConnection::GridConnection(GridConnection&& Other)
{
    *this = move(Other);
}

void GridConnection::SetName(string NewName)
{
    this->Name = NewName;
    this->Connection.SetName(NewName);
}

GridConnection& GridConnection::operator=(GridConnection&& Other)
{
    this->Connection = move(Other.Connection);
    
    this->Name = Other.Name;
    this->Connection.SetName(Name);

    for (shared_ptr<IParser> Parser: Other.Parsers)
    {
        AddParser(Parser);
    } 
    Other.Parsers.clear();

    for (pair<string, shared_ptr<ISerializer>> Pair: Other.Serializers)
    {
        AddSerializer(Pair.second);
    } 
    Other.Serializers.clear();
    
    return *this;
}

bool GridConnection::operator==(GridConnection& Other)
{
    return Other.Connection == this->Connection;
}

void GridConnection::CopyCommInterfaces(const vector<shared_ptr<IParser>>& Parsers, const unordered_map<string, shared_ptr<ISerializer>>& Serializers)
{
    for (shared_ptr<IParser> Parser: Parsers)
    {
        AddParser(Parser);
    }

    for (pair<string, shared_ptr<ISerializer>> Pair: Serializers)
    {
        AddSerializer(Pair.second);
    } 
}

void GridConnection::AddParser(shared_ptr<IParser>& Parser)
{
    Connection.AddParser(Parser);
    
    for(shared_ptr<IParser> LocalParser: Parsers)
    {
        if (LocalParser->GetType() == Parser->GetType())
        {
            return;
        }
    }
    
    this->Parsers.push_back(shared_ptr<IParser>(Parser));
}

void GridConnection::AddSerializer(shared_ptr<ISerializer>& Serializer)
{
    Connection.AddSerializer(Serializer);

    if (Serializers.find(Serializer->GetType()) != Serializers.end())
    {
        return;
    }

    this->Serializers[Serializer->GetType()] = shared_ptr<ISerializer>(Serializer);
}

int GridConnection::Connect(string Host, string Port, bool IsWorker)
{
    int Result = Connection.Connect(Host, Port); 
    if (Result == 0)
    {
        Connection.AddParsers(Parsers);
        Connection.AddSerializers(Serializers);
        Connection.Send(unique_ptr<IMessage>((IMessage*) new SendJobPolicyMessage(IsWorker)));
    }

    return Result;
}

int GridConnection::SendMessage(const unique_ptr<IMessage>& Msg)
{
    return Connection.Send(Msg);
}

int GridConnection::RecvMessage(unique_ptr<IMessage>& Msg)
{
    return Connection.Recv(Msg);
}

int GridConnection::SendJob(shared_ptr<IJob>& Job, vector<Argument>& Input)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new SendJobMessage(Job, Input)));
}

int GridConnection::SendJobOutput(shared_ptr<IJob>& Job, vector<Argument>& Output)
{
    return Connection.Send(
        unique_ptr<IMessage>((IMessage*) 
            new SendJobOutputMessage(Job->GetUniqueDescriptor(), Output)));
}

int GridConnection::CancelJob(shared_ptr<IJob>& Job)
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