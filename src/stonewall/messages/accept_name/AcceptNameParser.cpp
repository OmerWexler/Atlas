#pragma once

#include "Utils.h"
#include "AcceptNameParser.h"
#include "AcceptNameMessage.h"

using namespace std;


string AcceptNameParser::GetType() const
{
    return AcceptNameMessage::TYPE;
}

void AcceptNameParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    bool Accepted = SMsg.substr(GetType().length(), 1) == "1";
    string Name = SMsg.substr(GetType().length() + 1);

    Message.reset((IMessage*) DBG_NEW AcceptNameMessage(Accepted, Name));
}

bool AcceptNameParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, GetType().length()) == GetType();
}