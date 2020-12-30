#pragma once

#include <string>
#include <memory>

#include "IMessage.h"

using namespace std;

class ISerializer
{
public:
    virtual string GetType() const = 0;
    virtual string Serialize(const unique_ptr<IMessage>& Message) const = 0;

    virtual ISerializer* Clone() = 0;

    virtual ~ISerializer() {};
};