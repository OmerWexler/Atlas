#pragma once

#include "Utils.h"
#include "SendJobPolicyParser.h"
#include "SendJobPolicyMessage.h"

using namespace std;

string SendJobPolicyParser::GetType() const
{
    return SendJobPolicyMessage::TYPE;
}

void SendJobPolicyParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    bool AcceptJobs = SMsg.substr(SMsg.length() - 1) == "1";
    Message.reset((IMessage*) DBG_NEW SendJobPolicyMessage(AcceptJobs));
}

bool SendJobPolicyParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}