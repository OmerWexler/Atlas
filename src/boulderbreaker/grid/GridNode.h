#pragma once

#include <unordered_map>
#include <vector>
#include <thread> 
#include <memory> 

#include "BasicServer.h"
#include "GridConnection.h"
#include "IFunctionCore.h"
#include "IParser.h"
#include "ISerializer.h"
#include "Logger.h"
#include "SmartThread.h"

class GridNode
{
private:
    int BACK_LOG = 5;
    
    string Name;
    BasicServer NodeServer;
    GridConnection NodeAdmin;

    SmartThread ConnectionListener;
    SmartThread MemberManager;
    SmartThread ClientManager;

    vector<shared_ptr<IParser>> CollectiveParsers;
    unordered_map<string, shared_ptr<ISerializer>> CollectiveSerializers;
    vector<unique_ptr<IFunctionCore>> FunctionCores;

    unordered_map<int, GridConnection> Members;
    vector<int> AvailableMemberSlots;
    
    unordered_map<int, GridConnection> Clients;
    vector<int> AvailableClientSlots;

    void Init();
    string CreateMemberName();
    string CreateClientName();

    void AddConnectionToMap(unordered_map<int, GridConnection>& Map, string Type, vector<int>& Slots, GridConnection& Connection);

    void ConnectionListenerFunc();
    void MemberListenerFunc();
    void ClientListenerFunc();
    void IterateOnConnectionMap(unordered_map<int, GridConnection>& Map, vector<int>& Slots);

public:
    GridNode();
    GridNode(string Name);

    void SetName(string Name);

    void AddCollectiveParser(shared_ptr<IParser>& Parser);
    void AddCollectiveSerializer(shared_ptr<ISerializer>& Serializer);
    void AddFunctionCore(unique_ptr<IFunctionCore>& Core);

    int Setup(string Host, string Port);

    int ConnectToNode(string Host, string Port, bool IsWorker);

    GridConnection& GetAdmin() { return NodeAdmin; };

    GridConnection& GetMember(int MemberID);
    vector<int> GetMemberIDs();

    GridConnection& GetClient(int ClientID);
    vector<int> GetClientIDs();

    void Stop();

    ~GridNode();
};