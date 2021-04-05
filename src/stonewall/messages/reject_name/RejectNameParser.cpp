#pragma once

#include "Utils.h"
#include "RejectNameParser.h"
#include "RejectNameMessage.h"

using namespace std;

string RejectNameParser::GetType() const
{
    return RejectNameMessage::TYPE;
}

void RejectNameParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    string Name = SMsg.substr(GetType().length());

    Message.reset((IMessage*) DBG_NEW RejectNameMessage(Name));
}

bool RejectNameParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, GetType().length()) == GetType();
}