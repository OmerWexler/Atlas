#pragma once

#include "BasicConnection.h"
#include "Logger.h"

#ifdef _WIN32
#include "WinConnectionSocket.h"
#define ConnectionSocketType WinConnectionSocket
#endif

BasicConnection::BasicConnection(IConnectionSocket* Socket)
{
    this->ConnectionSocket = Socket;
    this->Name = Socket->GetName();
}

BasicConnection::BasicConnection(string Name)
{
    this->Name = Name;
    this->ConnectionSocket = (IConnectionSocket*) new ConnectionSocketType(Name);
}

int BasicConnection::Connect(string Host, string Port)
{
    return ConnectionSocket->Connect(Host, Port);
}

void BasicConnection::AddParser(IParser* Parser)
{
    Parsers[Parser->GetType()] = Parser;
}

void BasicConnection::AddSerializer(ISerializer* Serializer)
{
    Serializers[Serializer->GetType()] = Serializer;
}

int BasicConnection::Send(const IMessage* Msg)
{
    if (Serializers.find(Msg->GetType()) == Serializers.end())
    {
        Logger::GetInstance().Error(Name + " couldn't parse message of type " + Msg->GetType() + " because a corresponding serializer wasn't defined.");
        return -1;
    }

    string SMsg = Serializers[Msg->GetType()]->Serialize(Msg);
    string SMsgSize = to_string(SMsg.length());

    for(int i = SMsgSize.length(); i <= NUM_OF_BYTES_IN_MESSAGE_LEN; i++)
    {
        SMsgSize = "0" + SMsgSize;
    }
    
    return ConnectionSocket->Send(SMsgSize + SMsg);
}

IMessage* BasicConnection::Recv()
{
    string SMsg;
    ConnectionSocket->Recv(SMsg, NUM_OF_BYTES_IN_MESSAGE_LEN);
    ConnectionSocket->Recv(SMsg, atoi(SMsg.c_str()));

    for (std::pair<std::string, IParser*> element : Parsers)
    {
        if (element.second->CanParse(SMsg))
        {
            return element.second->Parse(SMsg);
        }
    }
    
    Logger::GetInstance().Error(Name + " couldn't parse message " + SMsg + " because a corresponding parser wasn't found.");
    return nullptr;
}

int BasicConnection::Disconnect()
{
    return 0;
}

BasicConnection::~BasicConnection()
{
    for (std::pair<std::string, IParser*> element : Parsers)
    {
        delete element.second;
    }

    for (std::pair<std::string, ISerializer*> element : Serializers)
    {
        delete element.second;
    }

    delete (ConnectionSocketType*) ConnectionSocket;
}