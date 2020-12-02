#pragma once

#include <memory>

#include "BasicConnection.h"
#include "Logger.h"

#ifdef _WIN32
#include "WinConnectionSocket.h"
#define ConnectionSocketType WinConnectionSocket
#endif

BasicConnection::BasicConnection(IConnectionSocket* Socket)
{
    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Socket);
    this->Name = ConnectionSocket->GetName();
}

BasicConnection::BasicConnection(string Name)
{
    this->Name = Name;
    this->ConnectionSocket = unique_ptr<IConnectionSocket>((IConnectionSocket*) new ConnectionSocketType(Name));
}

int BasicConnection::Connect(string Host, string Port)
{
    return ConnectionSocket->Connect(Host, Port);
}

void BasicConnection::AddParser(IParser* Parser)
{
    Parsers.push_back(Parser);
}

void BasicConnection::AddSerializer(ISerializer* Serializer)
{
    Serializers[Serializer->GetType()] = Serializer;
}

int BasicConnection::Send(const unique_ptr<IMessage>& Msg)
{
    if (Serializers.find(Msg->GetType()) == Serializers.end())
    {
        Logger::GetInstance().Error(Name + " couldn't parse message of type " + Msg->GetType() + " because a corresponding serializer wasn't defined.");
        return -1;
    }

    string SMsg = Serializers[Msg->GetType()]->Serialize(Msg.get());
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
            OutMsg.reset(parser->Parse(SMsg));
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