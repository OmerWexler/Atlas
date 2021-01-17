#pragma once

#include "CancelJobSerializer.h"
#include "CancelJobMessage.h"

string CancelJobSerializer::GetType() const
{
    return "CancelJob";
}

string CancelJobSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER + ((CancelJobMessage*) Message.get())->GetDescriptor();
    return SMsg;
};