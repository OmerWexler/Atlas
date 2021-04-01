#pragma once

#include "RequestNodePerformanceMessage.h"

using namespace std;

const string RequestNodePerformanceMessage::TYPE = "RequestNodePerformance";

string RequestNodePerformanceMessage::GetType() const
{
    return TYPE;
}