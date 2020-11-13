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
    string Name;
    WSADATA wsaData;
    SOCKET Socket = INVALID_SOCKET;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    const char *sendbuf = "this is a test";
    int iResult;

public:
    WinServerSocket(string Name, SOCKET Socket);
    WinServerSocket(string Name);
    
    int Bind(string Host, int Port);
    int Listen();
    IConnectionSocket* AcceptConnection(string ConnectionName);

    ~WinServerSocket();
};