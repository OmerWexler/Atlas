#pragma once

#include "SendJobPolicyParser.h"
#include "SendJobPolicyMessage.h"

using namespace std;

string SendJobPolicyParser::GetType() const
{
    return "SendJobPolicy";
}

void SendJobPolicyParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    bool AcceptJobs = SMsg.substr(SMsg.length() - 1) == "1";
    Message.reset((IMessage*) new SendJobPolicyMessage(AcceptJobs));
}

bool SendJobPolicyParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}

IParser* SendJobPolicyParser::Clone()
{
    return (IParser*) new SendJobPolicyParser();
}