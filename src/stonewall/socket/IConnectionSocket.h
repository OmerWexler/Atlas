#pragma once

#include <string>

using namespace std;

class IConnectionSocket 
{
public:
    virtual string GetName() const = 0;
    virtual void SetName(string NewName) = 0;

    virtual int Connect(string Host, string Port) = 0;
    virtual bool IsConnected() const = 0;

    virtual int Send(string Msg) = 0;
    virtual int Recv(string &Buffer, int Size) = 0;
    virtual int Disconnect() = 0;
    
    virtual ~IConnectionSocket() {};
};
