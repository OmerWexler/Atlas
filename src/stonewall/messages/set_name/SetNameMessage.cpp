#pragma once

#include "SetNameMessage.h"

using namespace std;

const string SetNameMessage::TYPE = "SetName";

SetNameMessage::SetNameMessage(string Name)
{
    this->Name = Name;
}

string SetNameMessage::GetType() const
{
    return TYPE;
}

string SetNameMessage::GetName() const
{
    return Name;
}