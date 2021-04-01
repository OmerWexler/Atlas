#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "Cloneable.h"

using namespace std;

class ISerializer
{
public:
    virtual string GetType() const = 0;
    virtual string Serialize(const unique_ptr<IMessage>& Message) const = 0;

    virtual ~ISerializer() {};
};

#define ATLS_CREATE_SHARED_SRLZR(type) shared_ptr<ISerializer>((ISerializer*) DBG_NEW type())