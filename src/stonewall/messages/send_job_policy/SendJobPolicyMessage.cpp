#pragma once

#include "SendJobPolicyMessage.h"

using namespace std;

const string SendJobPolicyMessage::TYPE = "SendJobPolicy";

SendJobPolicyMessage::SendJobPolicyMessage(bool Policy)
{
    this->Policy = Policy;
}

string SendJobPolicyMessage::GetType() const
{
    return TYPE;
}

bool SendJobPolicyMessage::GetPolicy()
{
    return Policy;
}