#pragma once

#include "IMessage.h"
#include "GridConnection.h"

template<class T>
class ICallback
{
public:
    virtual string GetMessageType() = 0;
    virtual void Callback(IMessage* Message, T& Connection) = 0;
};