#pragma once

#include "SendJobPolicySerializer.h"
#include "SendJobPolicyMessage.h"

using namespace std;

string SendJobPolicySerializer::GetType() const
{
    return "SendJobPolicy";
}

string SendJobPolicySerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendJobPolicyMessage* PolicyMsg = (SendJobPolicyMessage*) Message.get();
    string SMsg = "" + HEADER;
    if (PolicyMsg->GetPolicy())
        SMsg += "1";
    else
        SMsg =+ "0";
    
    return SMsg;
}

ISerializer* SendJobPolicySerializer::Clone()
{
    return (ISerializer*) new SendJobPolicySerializer();
}
