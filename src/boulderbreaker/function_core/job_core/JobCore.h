#pragma once

#include "IFunctionCore.h"

using namespace std;

class JobCore: IFunctionCore
{
private:
    unordered_map<string, unique_ptr<IJob>> LocalJobs;
    unordered_map<int, unordered_map<string, unique_ptr<IJob>>> MemberJobs;

public:
    string GetType() const;
    void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;

    ~JobCore() {};
};