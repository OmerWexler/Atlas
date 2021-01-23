#pragma once

#include "IMessage.h"
#include "PCPerformance.h"

using namespace std;

class RequestBestNodeMessage: public IMessage
{
private:
    int Range;
    struct PCPerformance& MinimumAcceptablePerformance = PCPerformance();

public:
    const static string TYPE;
    
    RequestBestNodeMessage(int Range, PCPerformance& MinimumAcceptablePerformance);
    string GetType() const override;
    int GetRange();
    PCPerformance& GetMinimumAcceptablePerformance();
};