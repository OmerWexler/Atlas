#pragma once

#include "GridNode.h"
#include "BasicServer.h"

#include "SendJobPolicySerializer.h"

#include "RequestBestNodeSerializer.h"
#include "SendBestNodeSerializer.h"

#include "SendJobSerializer.h"
#include "CancelJobSerializer.h"
#include "SendJobOutputSerializer.h"

#include "SendJobPolicyParser.h"

#include "RequestBestNodeParser.h"
#include "SendBestNodeParser.h"

#include "SendJobParser.h"
#include "CancelJobParser.h"
#include "SendJobOutputParser.h"

GridNode::GridNode(string Name)
{
    this->Name = Name;
    this->NodeServer = BasicServer("BasicServer - " + Name);
    Init();
}

void GridNode::Init()
{
    AddCollectiveParser((IParser*) new SendJobPolicyParser());
    AddCollectiveParser((IParser*) new RequestBestNodeParser());
    AddCollectiveParser((IParser*) new SendBestNodeParser());
    AddCollectiveParser((IParser*) new SendJobParser());
    AddCollectiveParser((IParser*) new CancelJobParser());
    AddCollectiveParser((IParser*) new SendJobOutputParser());

    AddCollectiveSerializer((ISerializer*) new SendJobPolicySerializer());
    AddCollectiveSerializer((ISerializer*) new RequestBestNodeSerializer());
    AddCollectiveSerializer((ISerializer*) new SendBestNodeSerializer());
    AddCollectiveSerializer((ISerializer*) new SendJobSerializer());
    AddCollectiveSerializer((ISerializer*) new CancelJobSerializer());
    AddCollectiveSerializer((ISerializer*) new SendJobOutputSerializer());
}

void GridNode::AddCollectiveParser(IParser* Parser)
{
    NodeServer.AddParser(Parser);

    for(int i = 0; i < CollectiveParsers.size(); i++)
    {
        if (CollectiveParsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    CollectiveParsers.push_back(Parser);
}

void GridNode::AddCollectiveSerializer(ISerializer* Serializer)
{
    if (CollectiveSerializers.find(Serializer->GetType()) == CollectiveSerializers.end())
    {
        CollectiveSerializers[Serializer->GetType()] = Serializer;
    }

    NodeServer.AddSerializer(Serializer);
}

void GridNode::AddHandler(IHandler* Handler)
{
    Handlers.push_back(Handler);
}

int GridNode::Setup(string Host, string Port)
{
    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
    {
        return Result;
    }

    Result = NodeServer.Listen(5);
    if (Result != 0)
    {
        return Result;
    }

    return 0;
}

int GridNode::AccpetNodeConnection()
{  
    string NewName = "Connection - " + to_string(Members.size() + Clients.size()) + " of " + Name;
    BasicConnection NewConnection{NewName}; 
    int Result = NodeServer.AcceptConnection(NewName, NewConnection);
    if (Result != 0) 
    {
        return Result;
    }

    QueuedConnections.push_back(GridConnection(NewConnection));
    return 0;
}

int GridNode::ConnectToNode(string Host, string Port, bool IsWorker)
{
    GridConnection NewConnection{"Connection To - " + Name};
    NewConnection.CopyCommInterfaces(CollectiveParsers, CollectiveSerializers);
    
    int Result = NewConnection.Connect(Host, Port, IsWorker);
    if (Result != 0)
    {
        return Result;
    }

    QueuedConnections.push_back(move(NewConnection));
    return 0;
}

int GridNode::SendJob(const IJob* Job, int Range, PCPerformance& MinimumAcceptablePerformance)
{
    return 0;
}

GridConnection& GridNode::GetConnection(int ConenctionID)
{
    return Members[ConenctionID];
}

void GridNode::GetConnectionIDs(vector<int>& OutIDs)
{
    
}