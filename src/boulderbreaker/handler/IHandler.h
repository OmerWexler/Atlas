#pragma once

#include "IMessage.h"
#include "GridConnection.h"

class IHandler
{
public:
    virtual void AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) const = 0;
    virtual bool IsMessageRelated(const unique_ptr<IMessage>& Message) const = 0;
};
