#pragma once

#define WIN32_LEAN_AND_MEAN

#include "IServerSocket.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

using namespace std;

class WinServerSocket: public IServerSocket
{
private:
    WSADATA wsaData;
    SOCKET Socket = INVALID_SOCKET;
    struct addrinfo HomeHints;

    // 0 = Blocked
    // 1 = Non Blocking
    u_long BlockMode = 0;

    string Name = "";
    string HomeAddress = "";

public:
    WinServerSocket(string Name, bool Blocking, SOCKET Socket);
    WinServerSocket(string Name, bool Blocking);
    
    string GetName() const;
    void SetName(string NewName);

    int Bind(string Host, string Port);
    int Listen(int Backlog);
    int AcceptConnection(string ConnectionName, unique_ptr<IConnectionSocket>& ConnectionSocket);
    void Close();

    virtual ~WinServerSocket();
};