#pragma once

#include "ASyncFunctionCore.h"

ASyncFunctionCore::ASyncFunctionCore(string Name, float PollFrequency)
{
    this->Name = Name;
    this->PollFrequency = PollFrequency;
}

void ASyncFunctionCore::StartCore()
{
    QueueThread = SmartThread(Name, PollFrequency, &ASyncFunctionCore::Periodic, this);
}

void ASyncFunctionCore::QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    MessageQueue.push_back(QueuedSet(
        Message,
        Sender
    ));
}

void ASyncFunctionCore::Periodic()
{
    this->HandleMessageFromQueue();
}

void ASyncFunctionCore::HandleMessageFromQueue()
{
    if (MessageQueue.size() > 0)
    {
        QueuedSet& Back = MessageQueue.back();

        HandleMessage(Back.Message, *Back.Sender);
        MessageQueue.pop_back();
    }
}

bool ASyncFunctionCore::IsRunning() const
{
    return QueueThread.GetIsRunning();
}

void ASyncFunctionCore::StopCore()
{
    return QueueThread.Stop();
}

ASyncFunctionCore::~ASyncFunctionCore() 
{
    QueueThread.Stop();
}