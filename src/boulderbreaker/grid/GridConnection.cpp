#include "GridConnection.h"
#include "BasicConnection.h"

#include "DisconnectMessage.h"
#include "SendNodePerformanceMessage.h"
#include "CancelJobMessage.h"
#include "SendJobPolicyMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"
#include "SetNameMessage.h"

#include "Utils.h"
#include "IJob.h"
#include "Logger.h"
#include "Singleton.h"

using namespace std;
GridConnection::GridConnection()
{
    Name = "UnnamedConnection";
    this->Connection = move(BasicConnection(Name, false));
}

GridConnection::GridConnection(string Name)
{
    this->Name = Name;
    this->Connection = move(BasicConnection(Name, false));
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

GridConnection& GridConnection::operator=(GridConnection&& Other)
{
    this->Connection = move(Other.Connection);
    
    this->Name = Other.Name;
    this->Host = Other.Host;
    this->Port = Other.Port;
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

void GridConnection::SetName(string NewName)
{
    this->Name = NewName;
    this->Connection.SetName(NewName);
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

int GridConnection::Connect(string Host, string Port, bool IsWorker, string NodeName)
{
    int Result = Connection.Connect(Host, Port); 
    if (Result == 0)
    {
        Connection.AddParsers(Parsers);
        Connection.AddSerializers(Serializers);
        Connection.Send(ATLS_CREATE_UNIQUE_MSG(SendJobPolicyMessage, IsWorker));
        Connection.Send(ATLS_CREATE_UNIQUE_MSG(SetNameMessage, NodeName));
    }

    this->Host = Host;
    this->Port = Port;

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

int GridConnection::Disconnect()
{
    Connection.Send(ATLS_CREATE_UNIQUE_MSG(DisconnectMessage));
    return Connection.Disconnect();
}