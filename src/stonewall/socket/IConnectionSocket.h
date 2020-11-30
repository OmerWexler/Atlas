#pragma once

#include <string>

using namespace std;

class IConnectionSocket 
{
public:
    virtual IConnectionSocket* operator= (const IConnectionSocket* Other) = 0;
    
    virtual string GetName() const = 0;
    virtual int Connect(string Host, string Port) = 0;
    virtual int Send(string Msg) = 0;
    virtual int Recv(string &Buffer, int Size) = 0;
    virtual int Disconnect() = 0;
    
};
