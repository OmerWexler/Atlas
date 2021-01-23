#pragma once

#include "SendBestNodeMessage.h"

using namespace std;

const string SendBestNodeMessage::TYPE = "SendBestNode";

SendBestNodeMessage::SendBestNodeMessage(const PCPerformance& NodePerformance)
{
    this->NodePerformance = NodePerformance;
}

string SendBestNodeMessage::GetType() const
{
    return TYPE;
}

PCPerformance& SendBestNodeMessage::GetNodePerformance()
{
    return NodePerformance;
}