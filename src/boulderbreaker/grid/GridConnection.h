#pragma once

#include <unordered_map>

#include "PCPerformance.h"
#include "Path.h"
#include "IJob.h"

#include "BasicConnection.h"

#include "IParser.h"
#include "ISerializer.h"
#include "IMessage.h"

class GridConnection
{
private:
    string Name;
    string Host;
    string Port;
    PCPerformance TopPerformance;
    Path TopPerformancePath;

    BasicConnection Connection;
    vector<shared_ptr<IParser>> Parsers;
    unordered_map<string, shared_ptr<ISerializer>> Serializers;

public:
    GridConnection(); 
    GridConnection(string Name); 
    GridConnection(BasicConnection& Connection);
    
    GridConnection(GridConnection&& Other);
    GridConnection& operator=(GridConnection&& Other);
    bool operator==(GridConnection& Other);

    void CopyCommInterfaces(const vector<shared_ptr<IParser>>& Parsers, const unordered_map<string, shared_ptr<ISerializer>>& Serializers);
    void AddParser(shared_ptr<IParser>& Parser);
    void AddSerializer(shared_ptr<ISerializer>& Serializer);

    int Connect(string Host, string Port, bool IsWorker, string NodeName);
    bool IsConnected() const { return Connection.IsConnected(); };

    void SwapKeys();
    int SendMessage(const unique_ptr<IMessage>& Msg);
    int RecvMessage(unique_ptr<IMessage>& Msg);

    void SetName(string NewName);
    string GetName() const { return Name; }
    
    void SetTopPerformance(PCPerformance& TopPerformance) { this->TopPerformance = TopPerformance; };
    PCPerformance GetTopPerformance() { return TopPerformance; }
    
    void SetTopPerformancePath(Path& TopPerformancePath) { this->TopPerformancePath = TopPerformancePath; };
    Path GetTopPerformancePath() { return TopPerformancePath; }
    
    string GetHost() const { return Host; }
    string GetPort() const { return Port; }

    int Disconnect();
};