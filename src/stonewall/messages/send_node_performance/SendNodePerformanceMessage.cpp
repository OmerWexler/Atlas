#pragma once

#include "SendNodePerformanceMessage.h"

using namespace std;

const string SendNodePerformanceMessage::TYPE = "SendNodePerformance";

SendNodePerformanceMessage::SendNodePerformanceMessage(const PCPerformance& NodePerformance)
{
    this->NodePerformance = NodePerformance;
}

string SendNodePerformanceMessage::GetType() const
{
    return TYPE;
}

PCPerformance& SendNodePerformanceMessage::GetNodePerformance()
{
    return NodePerformance;
}