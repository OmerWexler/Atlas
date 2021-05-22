#pragma once

#include <memory>

#include "Utils.h"
#include "IMessage.h"
#include "BasicConnection.h"
#include "Logger.h"
#include "SendRSAKeyMessage.h"
#include "SendRSAKeySerializer.h"

#ifdef _WIN32
#include "WinConnectionSocket.h"
#define ConnectionSocketType WinConnectionSocket
#endif

using namespace std;

void BasicConnection::Construct()
{
    EModule = RSAEncryptionModule();
    PeerPublicKey = RSAKey(RSAEncryptionModule::KeySize);

    SRSAParser = SendRSAKeyParser();
    AddSerializer(ATLS_CREATE_SHARED_SRLZR(SendRSAKeySerializer));
}

BasicConnection::BasicConnection()
{
    Construct();
    this->ConnectionSocket = unique_ptr<IConnectionSocket>((IConnectionSocket*) DBG_NEW ConnectionSocketType("", false));
}

BasicConnection::BasicConnection(unique_ptr<IConnectionSocket>& Socket)
{
    Construct();
    this->Name = Socket->GetName();
    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Socket.release());
}

BasicConnection::BasicConnection(string Name, bool Blocking)
{
    Construct();
    this->Name = Name;
    this->ConnectionSocket = unique_ptr<IConnectionSocket>((IConnectionSocket*) DBG_NEW ConnectionSocketType(Name, Blocking));
}

BasicConnection::BasicConnection(BasicConnection&& Other)
{
    (*this) = move(Other);
}

BasicConnection& BasicConnection::operator=(BasicConnection&& Other)
{
    this->Name = Other.Name;

    for (auto Parser: Other.Parsers)
    {
        AddParser(Parser);
    } 
    Other.Parsers.clear();

    for (auto Pair: Other.Serializers)
    {
        AddSerializer(Pair.second);
    } 
    Other.Serializers.clear();

    this->ConnectionSocket = unique_ptr<IConnectionSocket>(Other.ConnectionSocket.release());

    PeerPublicKey = Other.PeerPublicKey;
    EModule = Other.EModule;

    return *this;
}

bool BasicConnection::operator==(BasicConnection& Other)
{
    return Name == Other.Name && ConnectionSocket.get() == Other.ConnectionSocket.get();
}

void BasicConnection::SetName(string NewName)
{
    this->Name = NewName;
    this->ConnectionSocket->SetName(NewName);
}

int BasicConnection::SwapKeysWithPeer()
{
    if (!EModule.IsInitiated())
        EModule.GenerateKeys();

    unique_ptr<IMessage> PublicKeyMessage = ATLS_CREATE_UNIQUE_MSG(SendRSAKeyMessage, EModule.GetPublicKey());

    int Result = Send(PublicKeyMessage);
    if (Result < 0)
        return Result;

    Result = Recv(PublicKeyMessage);
    if (Result < 0)
        return Result;

    PeerPublicKey = ((SendRSAKeyMessage*)PublicKeyMessage.get())->GetKey();

    IsEncrypted = true;
    
    return 0;
}

int BasicConnection::RegenerateKey()
{
    EModule.GenerateKeys();
    unique_ptr<IMessage> PublicKeyMessage = ATLS_CREATE_UNIQUE_MSG(SendRSAKeyMessage, EModule.GetPublicKey());

    IsEncrypted = false;

    return Send(PublicKeyMessage);
}

int BasicConnection::Connect(string Host, string Port)
{
    int Result = ConnectionSocket->Connect(Host, Port);

    if (Result != 0)
        return Result;
    
    return SwapKeysWithPeer();
}

void BasicConnection::AddParser(shared_ptr<IParser>& Parser)
{
    for(unsigned int i = 0; i < Parsers.size(); i++)
    {
        if (Parsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    Parsers.push_back(shared_ptr<IParser>(Parser));
}

void BasicConnection::AddSerializer(shared_ptr<ISerializer>& Serializer)
{
    if (Serializers.find(Serializer->GetType()) != Serializers.end())
    {
        return;
    }

    Serializers[Serializer->GetType()] = shared_ptr<ISerializer>(Serializer);
}

void BasicConnection::AddParsers(vector<shared_ptr<IParser>>& Parsers)
{
    for(shared_ptr<IParser> Parser: Parsers)
    {
        AddParser(shared_ptr<IParser>(Parser));
    }
}

void BasicConnection::AddSerializers(unordered_map<string, shared_ptr<ISerializer>>& Serializers)
{
    for(pair<string, shared_ptr<ISerializer>> Pair : Serializers)
    {
        AddSerializer(shared_ptr<ISerializer>(Pair.second));
    }
}

int BasicConnection::Send(const unique_ptr<IMessage>& Msg)
{
    if (Serializers.find(Msg->GetType()) == Serializers.end())
    {
        Singleton<Logger>::GetInstance().Error(this->Name + " couldn't serialize message of type " + Msg->GetType() + " because a corresponding serializer wasn't defined.");
        return -1;
    }

    string SMsg = Serializers[Msg->GetType()]->Serialize(Msg);
    if (IsEncrypted)
        EModule.Encrypt(SMsg, PeerPublicKey);
    
    string SMsgSize = Utils::PadInt(SMsg.length(), NUM_OF_BYTES_IN_MESSAGE_LEN);

    return ConnectionSocket->Send(SMsgSize + SMsg);
}

int BasicConnection::Recv(unique_ptr<IMessage>& OutMsg)
{
    string SMsg;
    int Result;

    Result = ConnectionSocket->Recv(SMsg, NUM_OF_BYTES_IN_MESSAGE_LEN);
    if (Result < 0)
        return Result;
    
    Result = ConnectionSocket->Recv(SMsg, atoi(SMsg.c_str()));
    if (Result < 0)
        return Result;
    
    if (IsEncrypted)
        EModule.Decrypt(SMsg);

    if (SRSAParser.CanParse(SMsg))
    {
        unique_ptr<IMessage> KeyMessage = unique_ptr<IMessage>();
        SRSAParser.Parse(SMsg, KeyMessage);
        PeerPublicKey = ((SendRSAKeyMessage*)KeyMessage.get())->GetKey();

        IsEncrypted = true;

        return Recv(OutMsg);
    }
    else
    {
        for (shared_ptr<IParser> parser : Parsers)
        {
            if (parser->CanParse(SMsg))
            {
                parser->Parse(SMsg, OutMsg);
                return Result;
            }
        }
    }
    
    Singleton<Logger>::GetInstance().Error(Name + " couldn't parse message " + SMsg + " because a corresponding parser wasn't found.");
    return -1;
}

int BasicConnection::Disconnect()
{
    return ConnectionSocket->Disconnect();
}