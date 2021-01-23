#pragma once

#include "IMessage.h"

using namespace std;

class SendJobPolicyMessage: public IMessage
{
private:
    bool Policy;

public:
    const static string TYPE;

    SendJobPolicyMessage(bool Policy);
    string GetType() const override;
    bool GetPolicy();
};