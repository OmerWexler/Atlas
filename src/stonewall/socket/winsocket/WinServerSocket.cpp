#pragma once

#include <memory>
#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"

using namespace std;


WinServerSocket::WinServerSocket(string Name) 
{
    // Initialize Winsock
    int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Result != 0)
    {
        Logger::GetInstance().Error(Name + " - WSAStartup failed with error: " + to_string(Result));
    }

    ZeroMemory(&HomeHints, sizeof(HomeHints));
    HomeHints.ai_family = AF_UNSPEC;
    HomeHints.ai_socktype = SOCK_STREAM;
    HomeHints.ai_protocol = IPPROTO_TCP;

    this->Name = Name;
}

int WinServerSocket::Bind(string Host, string Port) 
{
    HomeAddress = Host + ":" + Port;
    addrinfo* ResolvedAddress = NULL;

    // Resolve the server address and port
    int Result = getaddrinfo(Host.c_str(), Port.c_str(), &HomeHints, &ResolvedAddress);
    if (Result != 0)
    {
        Logger::GetInstance().Error(Name + " couldn't resolve bind address of " + HomeAddress + " with error: " + to_string(Result));
        WSACleanup();
        return 1;
    }

    Socket = socket(ResolvedAddress->ai_family, ResolvedAddress->ai_socktype, ResolvedAddress->ai_protocol);
    if (Socket == INVALID_SOCKET)
    {
        Logger::GetInstance().Error(Name + " couldn't instantiate socket " + to_string(WSAGetLastError()));
        freeaddrinfo(ResolvedAddress);
        WSACleanup();
        return -1;
    }

    Result = bind(Socket, ResolvedAddress->ai_addr, (int)ResolvedAddress->ai_addrlen);
    if (Result == SOCKET_ERROR)
    {
        Logger::GetInstance().Error(Name + " had error binding to " + HomeAddress + ": " + to_string(WSAGetLastError()));
        freeaddrinfo(ResolvedAddress);
        closesocket(Socket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(ResolvedAddress);

    Logger::GetInstance().Info(Name + " bound to " + HomeAddress);
    return 0;
}

int WinServerSocket::Listen() 
{
    int Result = listen(Socket, SOMAXCONN);
    if (Result == SOCKET_ERROR)
    {
        Logger::GetInstance().Error(Name + " had error listening to connections: " + to_string(WSAGetLastError()));
        closesocket(Socket);
        WSACleanup();
        return -1;
    }

    Logger::GetInstance().Info(Name + " listening on " + HomeAddress);
    return 0;
}

int WinServerSocket::AcceptConnection(string ConnectionName, unique_ptr<IConnectionSocket>& ConnectionSocket)
{
    SOCKET ClientSocket = INVALID_SOCKET;
    ClientSocket = accept(Socket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET)
    {
        Logger::GetInstance().Error(Name + " had error while accepting client: " + to_string(WSAGetLastError()));
        closesocket(Socket);
        WSACleanup();
        return WSAGetLastError();
    } else {
        ConnectionSocket.reset((IConnectionSocket*) new WinConnectionSocket(ConnectionName, ClientSocket, HomeAddress));
        Logger::GetInstance().Info(Name + " accepted new connection " + ConnectionName);
        return 0;
    }
}

WinServerSocket::~WinServerSocket()
{
    closesocket(Socket);
    WSACleanup();
}