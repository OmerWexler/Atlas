#pragma once

#include "Utils.h"
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

using namespace std;

BasicServer::BasicServer(string Name, bool Blocking)
{
    this->Name = Name;
    this->ServerSocket = unique_ptr<IServerSocket>((IServerSocket*) DBG_NEW ServerSocketType(Name, Blocking));
}

BasicServer::BasicServer(BasicServer&& Other)
{
    (*this) = move(Other);
}

void BasicServer::SetName(string Name)
{
    this->Name = Name;
    this->ServerSocket->SetName(Name);
}

BasicServer& BasicServer::operator=(BasicServer&& Other)
{
    this->Name = Other.Name; 

    for (shared_ptr<IParser> Parser: Other.Parsers)
    {
        this->Parsers.push_back(Parser);
    } 
    Other.Parsers.clear();

    for (pair<string, shared_ptr<ISerializer>> Pair: Other.Serializers)
    {
        this->Serializers[Pair.first] = Pair.second;
    } 
    Other.Serializers.clear();

    this->ServerSocket = unique_ptr<IServerSocket>(Other.ServerSocket.release());
    return *this;
}

void BasicServer::AddParser(shared_ptr<IParser>& Parser)
{
    for(int i = 0; i < Parsers.size(); i++)
    {
        if (Parsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    Parsers.push_back(shared_ptr<IParser>(Parser));
}

void BasicServer::AddSerializer(shared_ptr<ISerializer>& Serializer)
{
    if (Serializers.find(Serializer->GetType()) != Serializers.end())
    {
        return;
    }

    Serializers[Serializer->GetType()] = shared_ptr<ISerializer>(Serializer);
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

    OutConnection = BasicConnection(NewConnectionSocket);
    for (shared_ptr<IParser> Parser : Parsers)
    {
        OutConnection.AddParser(Parser);
    }

    for (pair<string, shared_ptr<ISerializer>> element: Serializers)
    {
        OutConnection.AddSerializer(element.second);
    }
    return 0;
}

void BasicServer::Close()
{
    if (ServerSocket.get())
        ServerSocket->Close();
}

BasicServer::~BasicServer()
{
    Close();
}