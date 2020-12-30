#pragma once

#include "SendJobPolicyParser.h"
#include "SendJobPolicyMessage.h"

using namespace std;

const string SendJobPolicyParser::HEADER = "SJP";

string SendJobPolicyParser::GetType() const
{
    return "SendJobPolicy";
}

IMessage* SendJobPolicyParser::Parse(const string& SMsg)
{
    bool AcceptJobs = SMsg.substr(SMsg.length() - 1) == "1";
    return (IMessage*) new SendJobPolicyMessage(AcceptJobs);
}

bool SendJobPolicyParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}

IParser* SendJobPolicyParser::Clone()
{
    return (IParser*) new SendJobPolicyParser();
}