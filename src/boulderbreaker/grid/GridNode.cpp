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

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void CPSleep(int SleepSeconds)
{
#ifdef LINUX
    usleep(SleepSeconds * 1000 * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(SleepSeconds * 1000);
#endif
}

GridNode::GridNode(string Name)
{
    this->Name = Name;
    this->NodeServer = move(BasicServer("BasicServer - " + Name));
    Init();
}

void GridNode::Init()
{
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobPolicyParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new RequestBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendBestNodeParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new CancelJobParser()));
    AddCollectiveParser(shared_ptr<IParser>((IParser*) new SendJobOutputParser()));

    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobPolicySerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new RequestBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendBestNodeSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new CancelJobSerializer()));
    AddCollectiveSerializer(shared_ptr<ISerializer>((ISerializer*)new SendJobOutputSerializer()));
}

void GridNode::AddCollectiveParser(shared_ptr<IParser>& Parser)
{
    NodeServer.AddParser(Parser);

    for(int i = 0; i < CollectiveParsers.size(); i++)
    {
        if (CollectiveParsers[i]->GetType() == Parser->GetType())
        {
            return;
        }
    }

    CollectiveParsers.push_back(shared_ptr<IParser>(Parser));
}

void GridNode::AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer)
{
    if (CollectiveSerializers.find(Serializer->GetType()) == CollectiveSerializers.end())
    {
        CollectiveSerializers[Serializer->GetType()] = Serializer;
    }

    NodeServer.AddSerializer(shared_ptr<ISerializer>(Serializer));
}

void GridNode::AddHandler(unique_ptr<IHandler>& Handler)
{
    Handlers.push_back(unique_ptr<IHandler>(Handler.release()));
}

int GridNode::Setup(string Host, string Port)
{
    int Result;
    Result = NodeServer.Bind(Host, Port);
    if (Result != 0)
        return Result;

    ConnectionListener = thread(&GridNode::ConnectionListenerFunc, this);
    return 0;
}

void GridNode::ConnectionListenerFunc()
{
    int Result = -1;
    while (Result != 0)
    {
        Result = NodeServer.Listen(BACK_LOG);
        CPSleep(1);
    }

    while (true)
    {
        BasicConnection NewConnection{}; 
        int Result = NodeServer.AcceptConnection("", NewConnection);
        if (Result -= 0)
            QueuedConnections.push_back(GridConnection(NewConnection));
    }
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

GridConnection& GridNode::GetConnection(int ConenctionID)
{
    return Members[ConenctionID];
}

void GridNode::GetMemberIDs(vector<int>& OutIDs)
{
    OutIDs.clear();
    
    for (auto& Member: Members)
    {
        OutIDs.push_back(Member.first);
    }
}

void GridNode::GetClientIDs(vector<int>& OutIDs)
{
    OutIDs.clear();
    for (auto& Client: Clients)
    {
        OutIDs.push_back(Client.first);
    }
}