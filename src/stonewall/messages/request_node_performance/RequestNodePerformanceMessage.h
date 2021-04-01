#pragma once

#include "IMessage.h"
#include "PCPerformance.h"

using namespace std;

class RequestNodePerformanceMessage: public IMessage
{
private:
    struct PCPerformance& Performance = PCPerformance();

public:
    const static string TYPE;
    
    string GetType() const override;
    int GetRange();
    PCPerformance& GetPerformance();
};