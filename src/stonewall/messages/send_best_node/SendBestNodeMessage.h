#pragma once

#include "IMessage.h"
#include "PCPerformance.h"

using namespace std;

class SendBestNodeMessage: public IMessage
{
private:
    struct PCPerformance& NodePerformance = PCPerformance();

public:
    inline SendBestNodeMessage(const PCPerformance& NodePerformance)
    {
        this->NodePerformance = NodePerformance;
    }

    inline string GetType() const override
    {
        return "SendBestNode";
    }

    inline PCPerformance& GetNodePerformance()
    {
        return NodePerformance;
    }
};