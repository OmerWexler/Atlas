#pragma once

#include "Utils.h"
#include "SendRSAKeyMessage.h"
#include "SendRSAKeySerializer.h"
#include "RSAEncryptionModule.h"
#include "SeperatorBasedMessage.h"

using namespace std;

SendRSAKeySerializer::SendRSAKeySerializer()
{
    SPBSerializer = SeperatorBasedSerializer();
}

string SendRSAKeySerializer::GetType() const
{
    return SendRSAKeyMessage::TYPE;
}

string SendRSAKeySerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendRSAKeyMessage* SRSAKMsg = (SendRSAKeyMessage*)Message.get();
    char* Buffer = DBG_NEW char[RSAEncryptionModule::BufferSize];

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SRSAKMsg->GetKey().Exponent.edit(Buffer);
    SPBMsg->AddValue(string(Buffer));

    SRSAKMsg->GetKey().Modulus.edit(Buffer);
    SPBMsg->AddValue(string(Buffer));

    delete[] Buffer;
    return GetType() + SPBSerializer.Serialize(unique_ptr<IMessage>(SPBMsg));;
}