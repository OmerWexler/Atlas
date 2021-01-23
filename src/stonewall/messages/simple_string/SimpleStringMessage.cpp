#pragma once

#include "SimpleStringMessage.h"

using namespace std;

const string SimpleStringMessage::TYPE = "SimpleString";

SimpleStringMessage::SimpleStringMessage(string Value)
{
    this->Value = Value;
}

string SimpleStringMessage::GetType() const
{
    return TYPE;
}

string SimpleStringMessage::GetValue() const
{
    return Value;
}