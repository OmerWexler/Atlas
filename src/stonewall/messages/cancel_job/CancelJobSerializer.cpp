#pragma once

#include "CancelJobSerializer.h"
#include "CancelJobMessage.h"

const string CancelJobSerializer::HEADER = "CJ";

string CancelJobSerializer::GetType() const
{
    return "CancelJob";
}

string CancelJobSerializer::Serialize(const IMessage* Message) const
{
    string SMsg = HEADER + ((CancelJobMessage*) Message)->GetDescriptor();
    return SMsg;
};

ISerializer* CancelJobSerializer::Clone()
{
    return (ISerializer*) new CancelJobSerializer();
};