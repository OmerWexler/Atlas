#pragma once

#include "IServerSocket.h"
#include "IConnectionSocket.h"
#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>

class BasicConnection
{
private:
    IServerSocket& ServerSocket;

    unordered_map<string, IParser> Parsers;
    unordered_map<string, ISerializer> Serializers;
public:
    BasicConnection(IConnectionSocket& Socket);
    BasicConnection();
    
    int Connect(string Host, string Port);
    void AddParser(IParser& Parser);
    void AddSerializer(ISerializer& Serializer);
    int SendMessage(IMessage& Msg);
    int RecvMessage(IMessage& Msg);
    int Disconnect();
    
};