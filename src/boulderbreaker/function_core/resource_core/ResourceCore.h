#pragma once

#include <unordered_map>

#include "IFunctionCore.h"
#include "PCPerformance.h"
#include "Path.h"

using namespace std;

class ResourceCore: public IFunctionCore
{
public:
    string GetType() const;
    void QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender);
    bool IsMessageRelated(const unique_ptr<IMessage>& Message) const;
    
    void SendNodePerformanceCallback(unique_ptr<IMessage>& Message, GridConnection& Sender);
    ~ResourceCore()=default;
};