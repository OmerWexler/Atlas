#pragma once

#include <thread>

#include "IMessage.h"
#include "GridConnection.h"

using namespace std;

class ThreadedFunctionCore
{
private:
    thread QueueThread;
    vector<unique_ptr<IMessage>> MessageQueue;

public:
    virtual string GetType() const = 0;

    virtual void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) = 0;
    virtual bool IsMessageRelated(const unique_ptr<IMessage>& Message) const = 0;

    void StartCore() const;
    bool IsRunning() const;
    int StopCore() const;

    virtual ~ThreadedFunctionCore();
};
