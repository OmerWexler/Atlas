#pragma once

#include "IMessage.h"
#include "GridConnection.h"

class IHandler
{
public:
    virtual string AddMessage(IMessage* Message, GridConnection& Sender) const = 0;
    virtual void IsMessageRelated(IMessage* Message) const = 0;
};