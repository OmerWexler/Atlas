#pragma once

#include "WinConnectionSocket.h"
#include "Logger.h"

using namespace std;


WinConnectionSocket::WinConnectionSocket(string Name) 
{
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

WinConnectionSocket::WinConnectionSocket(string Name, SOCKET Socket) 
{
    this->Name = Name;
    WinConnectionSocket::WinConnectionSocket(Name);
}

int WinConnectionSocket::Connect(string Host, int Port) 
{
    iResult = getaddrinfo(PCSTR(Host.c_str()), PCSTR(Port), &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return -1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        // Create a SOCKET for connecting to server
        Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (Socket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return -1;
        }

        // Connect to server.
        iResult = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(Socket);
            Socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (Socket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return -1;
    }

    return 0;
}

int WinConnectionSocket::Send(string Msg) 
{
    iResult = send(Socket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(Socket);
        WSACleanup();
        return -1;
    }

    Logger::Log(Name + " sent " + to_string(iResult));
    return 0;
}

string WinConnectionSocket::Recv(int Size) 
{
    return 0;
}

int WinConnectionSocket::Disconnect() 
{
    return 0;
}

WinConnectionSocket::~WinConnectionSocket()
{
    closesocket(Socket);
    WSACleanup();
}