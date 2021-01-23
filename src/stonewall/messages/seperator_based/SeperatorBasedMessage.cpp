#pragma once

#include "SeperatorBasedMessage.h"

using namespace std;

const string SeperatorBasedMessage::TYPE = "SeperatorBased";

SeperatorBasedMessage::SeperatorBasedMessage()
{
    this->Values = vector<string>();
}

string SeperatorBasedMessage::GetType() const
{
    return TYPE;
}

vector<string> SeperatorBasedMessage::GetValues()
{
    return Values;
}

void SeperatorBasedMessage::AddValue(string Value)
{
    Values.push_back(Value);
}