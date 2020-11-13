#pragma once

#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"

using namespace std;


WinServerSocket::WinServerSocket(string Name) 
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

int WinServerSocket::Bind(string Host, int Port) 
{
    Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (Socket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }

    return 0;
}

int WinServerSocket::Listen() 
{
    iResult = bind(Socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(Socket);
        WSACleanup();
        return -1;
    }

    freeaddrinfo(result);

    iResult = listen(Socket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(Socket);
        WSACleanup();
        return -1;
    }

    return 0;
}

IConnectionSocket* WinServerSocket::AcceptConnection(string ConnectionName)
{
    IConnectionSocket* ReturnSocket;
    
    SOCKET ClientSocket = accept(Socket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(Socket);
        WSACleanup();
        ReturnSocket = nullptr;
    } else {
        ReturnSocket = (IConnectionSocket*) &WinConnectionSocket(ConnectionName, ClientSocket);
    }
    
    return ReturnSocket;
}

WinServerSocket::~WinServerSocket()
{
    closesocket(Socket);
    WSACleanup();
}