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
    inline RequestBestNodeMessage(int Range, PCPerformance& MinimumAcceptablePerformance)
    {
        this->Range = Range;
        this->MinimumAcceptablePerformance = MinimumAcceptablePerformance;
    }

    inline string GetType() const override
    {
        return "RequestBestNode";
    }

    inline int GetRange()
    {
        return Range;
    }

    inline PCPerformance& GetMinimumAcceptablePerformance()
    {
        return MinimumAcceptablePerformance;
    }
};