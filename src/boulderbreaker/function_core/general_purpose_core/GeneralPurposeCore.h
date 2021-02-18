#pragma once

#include "IFunctionCore.h"

class GeneralPurposeCore: IFunctionCore
{
public:
    string GetType() const;
    void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
};