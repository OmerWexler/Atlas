#pragma once

#include <string>
#include "IMessage.h"

using namespace std;

class SendJobPolicyMessage: IMessage
{
private:
    bool Policy;

public:
    inline SendJobPolicyMessage(bool Policy)
    {
        this->Policy = Policy;
    }

    inline virtual string GetType() const override
    {
        return "SendJobPolicy";
    };

    inline bool GetPolicy()
    {
        return Policy;
    }
};