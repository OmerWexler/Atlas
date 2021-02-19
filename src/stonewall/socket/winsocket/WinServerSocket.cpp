#pragma once

#include <memory>
#include <thread>
#include <chrono>

#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"
#include "Utils.h"

using namespace std;

WinServerSocket::WinServerSocket(string Name, bool Blocking) 
{
    // Initialize Winsock
    int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Result != 0)
    {
        Singleton<Logger>::GetInstance().Error(Name + " - WSAStartup failed with error: " + to_string(Result));
    }

    ZeroMemory(&HomeHints, sizeof(HomeHints));
    HomeHints.ai_family = AF_UNSPEC;
    HomeHints.ai_socktype = SOCK_STREAM;
    HomeHints.ai_protocol = IPPROTO_TCP;

    this->Name = Name;
    if (Blocking)
        this->BlockMode = 0; 
    else
        this->BlockMode = 1; 
}

string WinServerSocket::GetName() const
{
    return Name;
}

void WinServerSocket::SetName(string NewName)
{
    this->Name = NewName;
}

int WinServerSocket::Bind(string Host, string Port) 
{
    HomeAddress = Host + ":" + Port;
    addrinfo* ResolvedAddress = NULL;

    // Resolve the server address and port
    int Result = getaddrinfo(Host.c_str(), Port.c_str(), &HomeHints, &ResolvedAddress);
    if (Result != 0)
    {
        Singleton<Logger>::GetInstance().Error(Name + " couldn't resolve bind address of " + HomeAddress + " with error: " + to_string(Result));
        return Result;
    }

    Socket = socket(ResolvedAddress->ai_family, ResolvedAddress->ai_socktype, ResolvedAddress->ai_protocol);
    if (Socket == INVALID_SOCKET)
    {
        int WSALastError = WSAGetLastError();
        Singleton<Logger>::GetInstance().Error(Name + " couldn't instantiate socket " + to_string(WSALastError));
        freeaddrinfo(ResolvedAddress);
        return WSALastError;
    }
    ioctlsocket(Socket, FIONBIO, &BlockMode);

    Result = ::bind(Socket, ResolvedAddress->ai_addr, (int)ResolvedAddress->ai_addrlen);
    if (Result == SOCKET_ERROR)
    {
        int WSALastError = WSAGetLastError();
        Singleton<Logger>::GetInstance().Error(Name + " had error binding to " + HomeAddress + ": " + to_string(WSALastError));
        freeaddrinfo(ResolvedAddress);
        closesocket(Socket);
        return WSALastError;
    }

    freeaddrinfo(ResolvedAddress);

    Singleton<Logger>::GetInstance().Info(Name + " bound to " + HomeAddress);
    return 0;
}

int WinServerSocket::Listen(int Backlog) 
{
    int Result = listen(Socket, Backlog);
    if (Result == SOCKET_ERROR)
    {
        Singleton<Logger>::GetInstance().Error(Name + " had error listening to connections: " + to_string(WSAGetLastError()));
        closesocket(Socket);
        return -1;
    }

    Singleton<Logger>::GetInstance().Info(Name + " listening on " + HomeAddress);
    return 0;
}

int WinServerSocket::AcceptConnection(string ConnectionName, unique_ptr<IConnectionSocket>& ConnectionSocket)
{
    SOCKET ClientSocket = INVALID_SOCKET;
    ClientSocket = accept(Socket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET)
    {
        int LastError = WSAGetLastError();
        if (LastError != 10035)
        {
            Singleton<Logger>::GetInstance().Error(Name + " had error while accepting client: " + to_string(LastError));
        }
        return LastError;
    } else {
        ConnectionSocket.reset((IConnectionSocket*) DBG_NEW WinConnectionSocket(ConnectionName, ClientSocket, HomeAddress));
        Singleton<Logger>::GetInstance().Info(Name + " accepted new connection " + ConnectionName);
        return 0;
    }
}

WinServerSocket::~WinServerSocket()
{
    closesocket(Socket);
    WSACleanup();
}