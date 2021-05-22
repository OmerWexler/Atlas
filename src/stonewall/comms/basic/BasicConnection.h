#pragma once

#include <unordered_map>
#include <memory>

#include "IServerSocket.h"
#include "IConnectionSocket.h"
#include "ISerializer.h"
#include "IParser.h"

#include "RSAKey.h"
#include "RSAEncryptionModule.h"
#include "SendRSAKeyParser.h"

class BasicConnection
{
private:
    const int NUM_OF_BYTES_IN_MESSAGE_LEN = 4;
    string Name;

    unique_ptr<IConnectionSocket> ConnectionSocket;

    vector<shared_ptr<IParser>> Parsers;
    unordered_map<string, shared_ptr<ISerializer>> Serializers;

    bool IsEncrypted = false;
    RSAKey PeerPublicKey;
    RSAEncryptionModule EModule;

    SendRSAKeyParser SRSAParser;

public:
    BasicConnection();
    BasicConnection(unique_ptr<IConnectionSocket>& Socket);
    BasicConnection(string Name, bool Blocking);

    void Construct();

    BasicConnection(BasicConnection&& Other);
    BasicConnection& operator=(BasicConnection&& Other);
    
    bool operator==(BasicConnection& Other);
    
    int Connect(string Host, string Port);
    int SwapKeysWithPeer();
    int RegenerateKey();
    bool IsConnected() const { return ConnectionSocket->IsConnected(); };

    void AddParser(shared_ptr<IParser>& Parser);
    void AddSerializer(shared_ptr<ISerializer>& Serializer);

    void AddParsers(vector<shared_ptr<IParser>>& Parsers);
    void AddSerializers(unordered_map<string, shared_ptr<ISerializer>>& Serializers);
    
    int Send(const unique_ptr<IMessage>& Msg);
    int Recv(unique_ptr<IMessage>& OutMsg);
    
    void SetName(string NewName);
    string GetName() { return this->Name; };

    int Disconnect();
};