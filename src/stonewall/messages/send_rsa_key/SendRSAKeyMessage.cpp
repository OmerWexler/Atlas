#pragma once

#include "SendRSAKeyMessage.h"

using namespace std;

const string SendRSAKeyMessage::TYPE = "SRSAK";

SendRSAKeyMessage::SendRSAKeyMessage(RSAKey Key)
{
    this->Key = Key;
}

string SendRSAKeyMessage::GetType() const
{
    return TYPE;
}

RSAKey SendRSAKeyMessage::GetKey() const
{
    return Key;
}