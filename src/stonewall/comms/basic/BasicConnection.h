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
    unique_ptr<IConnectionSocket> ConnectionSocket;

    vector<IParser*> Parsers;
    unordered_map<string, ISerializer*> Serializers;
public:
    BasicConnection(IConnectionSocket* Socket);
    BasicConnection(string Name);
    BasicConnection() {};

    BasicConnection& operator= (BasicConnection& Other);
    
    int Connect(string Host, string Port);
    void AddParser(IParser* Parser);
    void AddSerializer(ISerializer* Serializer);
    int Send(const unique_ptr<IMessage>& Msg);
    int Recv(unique_ptr<IMessage>& OutMsg);
    int Disconnect();
    
    ~BasicConnection();
};