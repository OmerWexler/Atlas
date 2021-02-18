#pragma once

#include "Utils.h"
#include "IMessage.h"
#include "SetNameParser.h"
#include "SetNameMessage.h"

using namespace std;

string SetNameParser::GetType() const
{
    return SetNameMessage::TYPE;
}

void  SetNameParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    string Name = SMsg.substr(GetType().size());
    Message.reset((IMessage*) DBG_NEW SetNameMessage(Name));
}

bool SetNameParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, GetType().size()) == GetType();
}