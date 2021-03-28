#pragma once

#include "Utils.h"
#include "RejectNameParser.h"
#include "RejectNameMessage.h"

using namespace std;


string AcceptNameParser::GetType() const
{
    return RejectNameMessage::TYPE;
}

void AcceptNameParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    string Name = SMsg.substr(GetType().length() + 1);

    Message.reset((IMessage*) DBG_NEW RejectNameMessage(Name));
}

bool AcceptNameParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, GetType().length()) == GetType();
}