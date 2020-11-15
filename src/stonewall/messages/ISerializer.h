#pragma once

#include "IMessage.h"

#include <string>

using namespace std;

class ISerializer
{
public:
    virtual string GetType() = 0;
    virtual string Serialize(IMessage* Message) = 0;

};