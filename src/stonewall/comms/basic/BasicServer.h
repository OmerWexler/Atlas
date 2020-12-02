#pragma once

#include "IServerSocket.h"
#include "BasicConnection.h"

#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>

class BasicServer
{
private:
    IServerSocket& ServerSocket;

    unordered_map<string, IParser> Parsers;
    unordered_map<string, ISerializer> Serializers;
public:
    void AddParser(IParser& Parser);
    void AddSerializer(ISerializer& Serializer);
    
    int Bind(string Host, string Port);
    int Listen();
    int AcceptConnection(BasicConnection& OutConnection);
    
};