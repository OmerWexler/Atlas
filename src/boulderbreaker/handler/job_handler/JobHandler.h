#pragma once

#include "IHandler.h"

class JobHandler: IHandler
{
public:
    void AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) const;
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
};