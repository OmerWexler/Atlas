#pragma once

#include "IMessage.h"

using namespace std;

class SendJobPolicyMessage: public IMessage
{
private:
    bool Policy;

public:
    inline SendJobPolicyMessage(bool Policy)
    {
        this->Policy = Policy;
    }

    inline string GetType() const override
    {
        return "SendJobPolicy";
    };

    inline bool GetPolicy()
    {
        return Policy;
    }
};