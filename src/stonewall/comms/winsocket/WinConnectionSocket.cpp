#pragma once

#include "WinConnectionSocket.h"
#include "Logger.h"

#include <string>

using namespace std;

void WinConnectionSocket::Construct(string Name)
{
    this->Name = Name;

    // Initialize Winsock
    int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Result != 0)
    {
        printf("WSAStartup failed with error: %d\n", Result);
        Logger::GetInstance()->Error(Name + " - WSAStartup failed with error: " + to_string(Result));
    }

    // Setup hints
    ZeroMemory(&ServerAddressHints, sizeof(ServerAddressHints));
    ServerAddressHints.ai_family = AF_UNSPEC;
    ServerAddressHints.ai_socktype = SOCK_STREAM;
    ServerAddressHints.ai_protocol = IPPROTO_TCP;
}

WinConnectionSocket::WinConnectionSocket()
{
    Construct("");
}

WinConnectionSocket::WinConnectionSocket(string Name) 
{
    Construct(Name);
}

WinConnectionSocket::WinConnectionSocket(string Name, SOCKET Socket, string ServerAddress) 
{  
    this->Connected = true;
    this->Socket = Socket;
    this->ServerAddress = ServerAddress;
    Construct(Name);
}

int WinConnectionSocket::Connect(string Host, string Port) 
{
    struct addrinfo *ServerAddress = NULL;
    int Result;

    // Resolve server address
    Result = getaddrinfo(Host.c_str(), Port.c_str(), &ServerAddressHints, &ServerAddress);
    if (Result != 0)
    {
        Logger::GetInstance()->Error(Name + " couldn't get server address info: " + to_string(Result));
        WSACleanup();
        return -1;
    }

    // Attempt to connect to an address until one succeeds
    for (struct addrinfo *ptr = ServerAddress; ptr != NULL; ptr = ptr->ai_next)
    {
        // Create a SOCKET for connecting to server
        Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (Socket == INVALID_SOCKET)
        {
            Logger::GetInstance()->Error(Name + " - socket instantiation failed with WAS error: " + to_string(WSAGetLastError()));
            WSACleanup();
            return -1;
        }

        // Connect to server.
        Result = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (Result == SOCKET_ERROR)
        {
            closesocket(Socket);
            Socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(ServerAddress);

    if (Socket == INVALID_SOCKET)
    {
        Logger::GetInstance()->Warning(Name + " unable to connect to " + Host + ":" + Port + "!");
        WSACleanup();
        return -1;
    }

    this->ServerAddress = Host + ":" + Port;
    Logger::GetInstance()->Info(Name + " connected to " + this->ServerAddress);
    Connected = true;
    return 0;
}

int WinConnectionSocket::Send(string Msg) 
{
    if (!Connected)
    {
        Logger::GetInstance()->Error(Name + " - socket must be connected to send messages!");
        return -1;
    }

    const char* CMsg = Msg.c_str();
    int len = (int)strlen(CMsg);

    
    int Result = send(Socket, CMsg, len, 0);
    if (Result == SOCKET_ERROR)
    {
        Logger::GetInstance()->Error(Name + " failed to send: \"" + Msg + "\" to " + ServerAddress + " with error: " + to_string(WSAGetLastError()));
        closesocket(Socket);
        WSACleanup();
        return -1;
    }
    
    Logger::GetInstance()->Info(Name + " sent " + Msg + " to " + this->ServerAddress);
    return Result;
}

int WinConnectionSocket::Recv(string& Buffer, int Size) 
{
    if (!Connected)
    {
        Logger::GetInstance()->Error(Name + " - socket must be connected to receive messages!");
        return -1;
    }

    char* recvbuf = new char [Size];

    int Result = recv(Socket, recvbuf, Size, 0);
    if (Result > 0)
    {
        Buffer = string(recvbuf, Size);
        Logger::GetInstance()->Info(Name + " received " + Buffer + " from " + ServerAddress);
    }
    else if (Result == 0)
    {
        Logger::GetInstance()->Warning(Name + " couldn't receive " + to_string(Size) + " bytes from" + ServerAddress + " because it disconnected");
    }
    else
    {
        Logger::GetInstance()->Error(Name + " - recv failed with error: " + to_string(WSAGetLastError()));
    }
    
    delete recvbuf;

    return Result;
}

int WinConnectionSocket::Disconnect() 
{
    int Result = shutdown(Socket, SD_SEND);
    if (Result == SOCKET_ERROR)
    {
        Logger::GetInstance()->Error(Name + " - shutdown failed with error: " + to_string(WSAGetLastError()));
        closesocket(Socket);
        WSACleanup();
        return -1;
    }

    Logger::GetInstance()->Info(Name + " shutdown");
    return 0;
}

WinConnectionSocket::~WinConnectionSocket()
{
    closesocket(Socket);
    WSACleanup();
}