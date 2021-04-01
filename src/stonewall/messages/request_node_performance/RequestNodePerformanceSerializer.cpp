#pragma once

#include "Utils.h"
#include "RequestNodePerformanceSerializer.h"
#include "RequestNodePerformanceMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

string RequestNodePerformanceSerializer::GetType() const
{
    return RequestNodePerformanceMessage::TYPE;
};

string RequestNodePerformanceSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER + "";
    return SMsg;
};