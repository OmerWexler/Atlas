#pragma once

#include "DisconnectMessage.h"

using namespace std;

const string DisconnectMessage::TYPE = "Disconnect";

DisconnectMessage::DisconnectMessage()
{
}

string DisconnectMessage::GetType() const
{
    return TYPE;
}