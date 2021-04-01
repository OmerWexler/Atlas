#pragma once

#include "IMessage.h"

using namespace std;

class DisconnectMessage: IMessage
{
public:
    const static string TYPE;
    
    DisconnectMessage();
    string GetType() const override;
};