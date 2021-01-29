#pragma once

#include <memory>

#include "IFunctionCore.h"
#include "Logger.h"
#include "SimpleStringMessage.h"

class TestCore: IFunctionCore
{
public:
    string GetType() const
    {
        return "TestCore";
    }

    void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
    {
        Singleton<Logger>::GetInstance().Debug("SS Message - " + ((SimpleStringMessage*) Message.get())->GetValue());
        Singleton<Logger>::GetInstance().Debug("From - " + Sender.GetName());
    }

    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const
    {
        return Message->GetType() == "SimpleString";
    }
};