#pragma once

#include "SendJobPolicySerializer.h"
#include "SendJobPolicyMessage.h"

using namespace std;

const string SendJobPolicySerializer::HEADER = "SJP";

string SendJobPolicySerializer::GetType() const
{
    return "SendJobPolicy";
}

string SendJobPolicySerializer::Serialize(const IMessage* Message) const
{
    SendJobPolicyMessage* PolicyMsg = (SendJobPolicyMessage*) Message;
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
