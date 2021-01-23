#pragma once

#include "SimpleStringMessage.h"
#include "SimpleStringSerializer.h"

using namespace std;

string SimpleStringSerializer::GetType() const
{
    return SimpleStringMessage::TYPE;
}

string SimpleStringSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    return ((SimpleStringMessage*) Message.get())->GetValue();
}