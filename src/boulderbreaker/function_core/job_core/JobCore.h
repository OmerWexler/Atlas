#pragma once

#include "ASyncFunctionCore.h"

#define DEFAULT_POLL_FREQUENCY 0.02f
using namespace std;

class JobCore: public ASyncFunctionCore
{
private:
    unordered_map<string, shared_ptr<IJob>> LocalJobs;
    void SendJobMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender);
    void CancelJobMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender);
    void SendJobOutputMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender);

protected:
    void HandleMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    void Periodic();

public:
    JobCore(string Name, float PollFrequency): ASyncFunctionCore(Name, PollFrequency) {};
    JobCore(string Name): ASyncFunctionCore(Name, DEFAULT_POLL_FREQUENCY) {};

    string GetType() const;
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
    void StopCore() override;
    
    ~JobCore()=default;
};