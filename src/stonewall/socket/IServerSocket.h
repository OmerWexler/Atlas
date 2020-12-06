#pragma once

#include <string>
#include "IConnectionSocket.h"

using namespace std;

class IServerSocket 
{
public:
    virtual int Bind(string Host, string Port) = 0;
    virtual int Listen(int Backlog) = 0;
    virtual int AcceptConnection(string ConnectionName, unique_ptr<IConnectionSocket>& ConnectionSocket) = 0;

    virtual ~IServerSocket() {};
};
