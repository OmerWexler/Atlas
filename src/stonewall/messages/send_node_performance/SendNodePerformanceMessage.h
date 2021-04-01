#pragma once

#include "IMessage.h"
#include "PCPerformance.h"

using namespace std;

class SendNodePerformanceMessage: public IMessage
{
private:
    struct PCPerformance& NodePerformance = PCPerformance();

public:
    const static string TYPE;
    
    SendNodePerformanceMessage(const PCPerformance& NodePerformance);
    string GetType() const override;
    PCPerformance& GetNodePerformance();
};