#pragma once

#include "IFunctionCore.h"

class JobCore: IFunctionCore
{
public:
    string GetType() const;
    void AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
};