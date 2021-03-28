#pragma once

#include <string>
#include <memory>

#include "IConnectionSocket.h"

using namespace std;

class IServerSocket 
{
public:
    virtual string GetName() const = 0;
    virtual void SetName(string NewName) = 0;

    virtual int Bind(string Host, string Port) = 0;
    virtual int Listen(int Backlog) = 0;
    virtual int AcceptConnection(string ConnectionName, unique_ptr<IConnectionSocket>& ConnectionSocket) = 0;
    virtual void Close() = 0;

    virtual ~IServerSocket() {};
};
