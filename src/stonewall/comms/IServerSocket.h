#pragma once

#include <string>
#include "IConnectionSocket.h"

using namespace std;

class IServerSocket 
{
public:
    virtual int Bind(string Host, string Port) = 0;
    virtual int Listen() = 0;
    virtual IConnectionSocket* AcceptConnection(string ConnectionName) = 0;
};
