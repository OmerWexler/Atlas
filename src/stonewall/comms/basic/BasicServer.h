#pragma once

#include "IServerSocket.h"
#include "BasicConnection.h"

#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>
#include <memory>

class BasicServer
{
private:
    string Name = "";
    unique_ptr<IServerSocket> ServerSocket;

    vector<shared_ptr<IParser>> Parsers;
    unordered_map<string, shared_ptr<ISerializer>> Serializers;
public:
    BasicServer() {};
    BasicServer(string Name);

    BasicServer(BasicServer&& Other);
    BasicServer& operator=(BasicServer&& Other);
    
    void AddParser(shared_ptr<IParser>& Parser);
    void AddSerializer(shared_ptr<ISerializer>& Serializer);
    
    int Bind(string Host, string Port);
    int Listen(int Backlog);
    int AcceptConnection(string Name, BasicConnection& OutConnection);
};