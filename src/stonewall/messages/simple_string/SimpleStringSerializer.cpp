#pragma once

#include "SimpleStringMessage.h"
#include "SimpleStringSerializer.h"

using namespace std;

string SimpleStringSerializer::GetType() const
{
    return "SimpleString";
}

string SimpleStringSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    return ((SimpleStringMessage*) Message.get())->GetValue();
}