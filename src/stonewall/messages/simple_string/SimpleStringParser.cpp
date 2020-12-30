#pragma once

#include "IMessage.h"
#include "SimpleStringParser.h"
#include "SimpleStringMessage.h"

using namespace std;

string SimpleStringParser::GetType() const
{
    return "SimpleString";
}

IMessage* SimpleStringParser::Parse(const string& SMsg)
{
    return (IMessage*) new SimpleStringMessage(SMsg);
}

bool SimpleStringParser::CanParse(const string& SMsg) const
{
    return true;
}

IParser* SimpleStringParser::Clone()
{
    return (IParser*) new SimpleStringParser();
}