#pragma once

#include "IMessage.h"
#include "SimpleStringParser.h"
#include "SimpleStringMessage.h"

using namespace std;

string SimpleStringParser::GetType() const
{
    return "SimpleString";
}

void  SimpleStringParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    Message.reset((IMessage*) new SimpleStringMessage(SMsg));
}

bool SimpleStringParser::CanParse(const string& SMsg) const
{
    return true;
}