#pragma once

#include "CancelJobParser.h"
#include "CancelJobMessage.h"

using namespace std;

string CancelJobParser::GetType() const
{
    return "CancelJob";
}

void CancelJobParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    string Descriptor = SMsg.substr(HEADER.length(), SMsg.length());
    Message.reset((IMessage*) new CancelJobMessage(Descriptor));
}

bool CancelJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}