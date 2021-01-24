#pragma once

#include "IMessage.h"
#include "GridConnection.h"

class IFunctionCore
{
public:
    virtual string GetType() const = 0;
    virtual void AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) = 0;
    virtual bool IsMessageRelated(const unique_ptr<IMessage>& Message) const = 0;

    virtual ~IFunctionCore() {};
};
