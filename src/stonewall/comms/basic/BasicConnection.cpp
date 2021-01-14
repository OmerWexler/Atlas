#pragma once

#include <memory>

#include "IMessage.h"
#include "BasicConnection.h"
#include "Logger.h"

#ifdef _WIN32
#include "WinConnectionSocket.h"
#define ConnectionSocketType WinConnectionSocket
#endif

using namespace std;

BasicConnection::BasicConnection(IConnectionSocket* Socket)
{
    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Socket);
    this->Name = ConnectionSocket->GetName();
}

BasicConnection::BasicConnection()
{
    this->Name = Name;
    this->ConnectionSocket = unique_ptr<IConnectionSocket>((IConnectionSocket*) new ConnectionSocketType(""));
}

BasicConnection::BasicConnection(string Name)
{
    this->Name = Name;
    this->ConnectionSocket = unique_ptr<IConnectionSocket>((IConnectionSocket*) new ConnectionSocketType(Name));
}

BasicConnection::BasicConnection(BasicConnection&& Other)
{
    this->Name = Other.Name;
    this->Parsers = vector<IParser*>(Other.Parsers);
    this->Serializers = unordered_map<string, ISerializer*>(Other.Serializers);
    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Other.ConnectionSocket.release());
}

BasicConnection& BasicConnection::operator=(BasicConnection&& Other)
{
    this->Name = Other.Name;
    this->Parsers = vector<IParser*>(Other.Parsers);
    this->Serializers = unordered_map<string, ISerializer*>(Other.Serializers);
    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Other.ConnectionSocket.release());
    return *this;
}

int BasicConnection::Connect(string Host, string Port)
{
    return ConnectionSocket->Connect(Host, Port);
}

void BasicConnection::AddParser(IParser* Parser)
{
    for(int i = 0; i < Parsers.size(); i++)
    {
        if (Parsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    Parsers.push_back(Parser);
}

void BasicConnection::AddSerializer(ISerializer* Serializer)
{
    if (Serializers.find(Serializer->GetType()) != Serializers.end())
    {
        return;
    }

    Serializers[Serializer->GetType()] = Serializer;
}

void BasicConnection::AddParsers(vector<IParser*> Parsers)
{
    for(IParser* Parser: Parsers)
    {
        AddParser(Parser);
    }
}

void BasicConnection::AddSerializers(unordered_map<string, ISerializer*> Serializers)
{
    for(pair<string, ISerializer*> Pair : Serializers)
    {
        AddSerializer(Pair.second);
    }
}

int BasicConnection::Send(const unique_ptr<IMessage>& Msg)
{
    if (Serializers.find(Msg->GetType()) == Serializers.end())
    {
        Logger::GetInstance().Error(this->Name + " couldn't serialize message of type " + Msg->GetType() + " because a corresponding serializer wasn't defined.");
        return -1;
    }

    string SMsg = Serializers[Msg->GetType()]->Serialize(Msg);
    string SMsgSize = to_string(SMsg.length());

    for(size_t i = SMsgSize.length(); i < NUM_OF_BYTES_IN_MESSAGE_LEN; i++)
    {
        SMsgSize = "0" + SMsgSize;
    }
    
    return ConnectionSocket->Send(SMsgSize + SMsg);
}

int BasicConnection::Recv(unique_ptr<IMessage>& OutMsg)
{
    string SMsg;
    ConnectionSocket->Recv(SMsg, NUM_OF_BYTES_IN_MESSAGE_LEN);
    ConnectionSocket->Recv(SMsg, atoi(SMsg.c_str()));

    for (IParser* parser : Parsers)
    {
        if (parser->CanParse(SMsg))
        {
            parser->Parse(SMsg, OutMsg);
            return 0;
        }
    }
    
    Logger::GetInstance().Error(Name + " couldn't parse message " + SMsg + " because a corresponding parser wasn't found.");
    return -1;
}

int BasicConnection::Disconnect()
{
    return ConnectionSocket->Disconnect();
}

BasicConnection::~BasicConnection()
{
    for (IParser* parser : Parsers)
    {
        delete parser;
    }

    for (std::pair<std::string, ISerializer*> element : Serializers)
    {
        delete element.second;
    }
}