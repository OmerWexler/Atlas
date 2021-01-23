#pragma once

#include "RequestBestNodeMessage.h"

using namespace std;

const string RequestBestNodeMessage::TYPE = "RequestBestNode";

RequestBestNodeMessage::RequestBestNodeMessage(int Range, PCPerformance& MinimumAcceptablePerformance)
{
    this->Range = Range;
    this->MinimumAcceptablePerformance = MinimumAcceptablePerformance;
}

string RequestBestNodeMessage::GetType() const
{
    return TYPE;
}

int RequestBestNodeMessage::GetRange()
{
    return Range;
}

PCPerformance& RequestBestNodeMessage::GetMinimumAcceptablePerformance()
{
    return MinimumAcceptablePerformance;
}