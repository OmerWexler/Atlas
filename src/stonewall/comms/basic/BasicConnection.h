#pragma once

#include "IServerSocket.h"
#include "IConnectionSocket.h"
#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>

class BasicConnection
{
private:
    const int NUM_OF_BYTES_IN_MESSAGE_LEN = 4;
    string Name;
    IConnectionSocket* ConnectionSocket;

    unordered_map<string, IParser*> Parsers;
    unordered_map<string, ISerializer*> Serializers;
public:
    BasicConnection(IConnectionSocket* Socket);
    BasicConnection(string Name);
    
    int Connect(string Host, string Port);
    void AddParser(IParser* Parser);
    void AddSerializer(ISerializer* Serializer);
    int Send(const IMessage* Msg);
    IMessage* Recv();
    int Disconnect();
    
    ~BasicConnection();
};