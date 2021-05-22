#pragma once

#include "Utils.h"
#include "SendRSAKeyParser.h"
#include "SendRSAKeyMessage.h"
#include "RSAEncryptionModule.h"
#include "SeperatorBasedMessage.h"

#include <string.h>

using namespace std;

SendRSAKeyParser::SendRSAKeyParser()
{
    SPBParser = SeperatorBasedParser();
}

string SendRSAKeyParser::GetType() const
{
    return SendRSAKeyMessage::TYPE;
}

void  SendRSAKeyParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(GetType().length()), USPBMsg);
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();
    
    const char* Buffer;

    mpuint& Exponent = mpuint(RSAEncryptionModule::KeySize);
    Buffer = Values[0].c_str();
    Exponent.scan(Buffer);

    mpuint& Modulus = mpuint(RSAEncryptionModule::KeySize);
    Buffer = Values[1].c_str();
    Modulus.scan(Buffer);

    Message.reset((IMessage*) DBG_NEW SendRSAKeyMessage(RSAKey(RSAEncryptionModule::KeySize, Exponent, Modulus)));
}

bool SendRSAKeyParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, GetType().size()) == GetType();
}