#pragma once

#include "SendNodePerformanceMessage.h"

using namespace std;

const string SendNodePerformanceMessage::TYPE = "SendNodePerformance";

SendNodePerformanceMessage::SendNodePerformanceMessage(const PCPerformance& NodePerformance)
{
    this->NodePerformance = NodePerformance;
}

SendNodePerformanceMessage::SendNodePerformanceMessage(const PCPerformance& NodePerformance, Path NodePath)
{
    this->NodePerformance = NodePerformance;
    this->NodePath = NodePath;
}

string SendNodePerformanceMessage::GetType() const
{
    return TYPE;
}

PCPerformance& SendNodePerformanceMessage::GetNodePerformance()
{
    return NodePerformance;
}

Path SendNodePerformanceMessage::GetPath()
{
    return NodePath;
}