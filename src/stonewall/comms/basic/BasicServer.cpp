#pragma once

#include "BasicServer.h"
#include "BasicConnection.h"

#include "IServerSocket.h"
#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>
#include <unordered_map>

#ifdef _WIN32
#include "WinServerSocket.h"
#define ServerSocketType WinServerSocket
#endif

BasicServer::BasicServer(string Name)
{
    this->Name = Name;
    this->ServerSocket = unique_ptr<IServerSocket>((IServerSocket*) new ServerSocketType(Name));
}

BasicServer::BasicServer(BasicServer&& Other)
{
    this->Name = Other.Name; 
    this->Parsers = vector<IParser*>(Other.Parsers);
    this->Serializers = unordered_map<string, ISerializer*>(Other.Serializers);
    this->ServerSocket = unique_ptr<IServerSocket>(Other.ServerSocket.release());
}

BasicServer& BasicServer::operator=(BasicServer&& Other)
{
    this->Name = Other.Name; 
    this->Parsers = vector<IParser*>(Other.Parsers);
    this->Serializers = unordered_map<string, ISerializer*>(Other.Serializers);
    this->ServerSocket = unique_ptr<IServerSocket>(Other.ServerSocket.release());
    return *this;
}

void BasicServer::AddParser(IParser* Parser)
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

void BasicServer::AddSerializer(ISerializer* Serializer)
{
    if (Serializers.find(Serializer->GetType()) != Serializers.end())
    {
        return;
    }

    Serializers[Serializer->GetType()] = Serializer;
}

int BasicServer::Bind(string Host, string Port)
{
    return ServerSocket->Bind(Host, Port);
}

int BasicServer::Listen(int Backlog)
{
    return ServerSocket->Listen(Backlog);
}

int BasicServer::AcceptConnection(string Name, BasicConnection& OutConnection)
{
    unique_ptr<IConnectionSocket> NewConnectionSocket;
    int Result = ServerSocket->AcceptConnection(Name, NewConnectionSocket);
    if (Result != 0)
    {
        return Result;
    }

    OutConnection = BasicConnection(NewConnectionSocket.release());
    for (IParser* Parser : Parsers)
    {
        OutConnection.AddParser(Parser->Clone());
    }

    for (pair<string, ISerializer*> element: Serializers)
    {
        OutConnection.AddSerializer(element.second->Clone());
    }
    return 0;
}

BasicServer::~BasicServer()
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