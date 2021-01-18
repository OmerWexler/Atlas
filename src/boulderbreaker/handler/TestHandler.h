#pragma once

#include <memory>

#include "IHandler.h"
#include "Logger.h"
#include "SimpleStringMessage.h"

class TestHandler: IHandler
{
public:
    void AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) const
    {
        SingletonLogger::GetInstance().Debug("SS Message - " + ((SimpleStringMessage*) Message.get())->GetValue());
        SingletonLogger::GetInstance().Debug("From - " + Sender.GetName());
    }

    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const
    {
        return Message->GetType() == "SimpleString";
    }
};