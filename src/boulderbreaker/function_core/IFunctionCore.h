#pragma once

#include "IMessage.h"
#include "GridConnection.h"

class IFunctionCore
{
public:
    virtual string GetType() const = 0;
    virtual void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) = 0;
    virtual bool IsMessageRelated(const unique_ptr<IMessage>& Message) const = 0;

    virtual ~IFunctionCore() {};
};

#define ATLS_CREATE_UNIQUE_CORE(type, ...) unique_ptr<IFunctionCore>((IFunctionCore*) DBG_NEW type(__VA_ARGS__))