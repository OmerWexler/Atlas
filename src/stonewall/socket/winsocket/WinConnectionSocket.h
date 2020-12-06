#pragma once

#define WIN32_LEAN_AND_MEAN

#include "IConnectionSocket.h"

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

class WinConnectionSocket: public IConnectionSocket
{
private:
    WSADATA wsaData;
    SOCKET Socket = INVALID_SOCKET;
    struct addrinfo ServerAddressHints;

    string Name = "";
    string ServerAddress = "";
    bool Connected = false;

    void Construct(string Name);
public:
    WinConnectionSocket(string Name, SOCKET Socket, string ServerAddress);
    WinConnectionSocket(string Name);
    WinConnectionSocket();

    string GetName() const;

    int Connect(string Host, string Port);
    int Send(string Msg);
    int Recv(string &Buffer, int Size);
    int Disconnect();

    virtual ~WinConnectionSocket();
};