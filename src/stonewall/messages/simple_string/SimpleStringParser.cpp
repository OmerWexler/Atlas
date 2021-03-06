#pragma once

#include "Utils.h"
#include "IMessage.h"
#include "SimpleStringParser.h"
#include "SimpleStringMessage.h"

using namespace std;

string SimpleStringParser::GetType() const
{
    return SimpleStringMessage::TYPE;
}

void  SimpleStringParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    Message.reset((IMessage*) DBG_NEW SimpleStringMessage(SMsg));
}

bool SimpleStringParser::CanParse(const string& SMsg) const
{
    return true;
}