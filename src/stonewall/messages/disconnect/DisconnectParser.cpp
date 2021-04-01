#pragma once

#include "Utils.h"
#include "DisconnectParser.h"
#include "DisconnectMessage.h"

using namespace std;

string DisconnectParser::GetType() const
{
    return DisconnectMessage::TYPE;
}

void DisconnectParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    Message.reset((IMessage*) DBG_NEW DisconnectMessage());
}

bool DisconnectParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}