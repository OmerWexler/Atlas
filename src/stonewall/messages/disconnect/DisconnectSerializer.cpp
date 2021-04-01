#pragma once

#include "DisconnectSerializer.h"
#include "DisconnectMessage.h"

string DisconnectSerializer::GetType() const
{
    return DisconnectMessage::TYPE;
}

string DisconnectSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER + ""; 
    return SMsg;
};