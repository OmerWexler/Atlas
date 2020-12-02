#pragma once

#include "IMessage.h"

#include <string>

using namespace std;

class ISerializer
{
public:
    virtual string GetType() const = 0;
    virtual string Serialize(const IMessage* Message) const = 0;

};