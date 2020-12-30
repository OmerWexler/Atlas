#pragma once

#include "SimpleStringMessage.h"
#include "SimpleStringSerializer.h"

using namespace std;

string SimpleStringSerializer::GetType() const
{
    return "SimpleString";
}

string SimpleStringSerializer::Serialize(const IMessage* Message) const
{
    return ((SimpleStringMessage*) Message)->GetValue();
}

ISerializer* SimpleStringSerializer::Clone()
{
    return (ISerializer*) new SimpleStringSerializer();
}