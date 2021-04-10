#pragma once

#include "SmartThread.h"
#include "IMessage.h"
#include "GridConnection.h"
#include "IFunctionCore.h"

using namespace std;

struct QueuedSet
{
    unique_ptr<IMessage> Message;
    int SenderID;
    GridConnection* Sender = nullptr;

    QueuedSet(unique_ptr<IMessage>& Message, GridConnection& Sender)
    {
        this->Message = unique_ptr<IMessage>(Message.release());
        this->Sender = &Sender;
    }
};

class ASyncFunctionCore: public IFunctionCore
{
private:
    string Name = "UnnamedCore";
    float PollFrequency;
    SmartThread QueueThread;
    vector<SmartThread> MessageThreads;
    vector<QueuedSet> MessageQueue;

    void HandleMessageFromQueue();

protected:
    virtual void HandleMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) = 0;
    virtual void Periodic();

public:
    ASyncFunctionCore(string Name, float PollFrequency);

    virtual string GetType() const = 0;
    virtual bool IsMessageRelated(const unique_ptr<IMessage>& Message) const = 0;

    virtual void StartCore();
    virtual bool IsRunning() const;
    virtual void StopCore();
    
    void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);

    virtual ~ASyncFunctionCore();
};
