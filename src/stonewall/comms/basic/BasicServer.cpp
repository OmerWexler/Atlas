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

void BasicServer::AddParser(IParser* Parser)
{
    Parsers.push_back(Parser);
}

void BasicServer::AddSerializer(ISerializer* Serializer)
{
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
    if (Result == 0)
    {
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

    return -1;
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