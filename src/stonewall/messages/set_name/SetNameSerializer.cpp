#pragma once

#include "SetNameMessage.h"
#include "SetNameSerializer.h"

using namespace std;

string SetNameSerializer::GetType() const
{
    return SetNameMessage::TYPE;
}

string SetNameSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    return GetType() + ((SetNameMessage*) Message.get())->GetName();
}