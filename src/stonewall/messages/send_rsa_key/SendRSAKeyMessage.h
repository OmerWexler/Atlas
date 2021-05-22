#pragma once

#include "IMessage.h"
#include "RSAKey.h"

using namespace std;

class SendRSAKeyMessage: IMessage
{
private:
    RSAKey Key;
    bool m_IsPrivate;
    
public:
    const static string TYPE;

    SendRSAKeyMessage(RSAKey Key);
    string GetType() const override;
    RSAKey GetKey() const;
};