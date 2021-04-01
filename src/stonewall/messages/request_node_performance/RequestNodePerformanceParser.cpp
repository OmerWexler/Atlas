#pragma once

#include "Utils.h"
#include "RequestNodePerformanceParser.h"
#include "SeperatorBasedMessage.h"
#include "RequestNodePerformanceMessage.h"

using namespace std;

string RequestNodePerformanceParser::GetType() const
{
    return RequestNodePerformanceMessage::TYPE;
}

void RequestNodePerformanceParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    Message.reset(DBG_NEW RequestNodePerformanceMessage());
}

bool RequestNodePerformanceParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}