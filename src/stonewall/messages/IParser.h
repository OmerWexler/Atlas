#pragma once

#include <string>
#include <memory>

#include "IMessage.h"

using namespace std;

class IParser
{
public:
    virtual string GetType() const = 0;
    virtual void Parse(const string& SMsg, unique_ptr<IMessage>& Message) = 0;
    virtual bool CanParse(const string& SMsg) const = 0;
    
    virtual ~IParser() {};
};

#define ATLS_CREATE_SHARED_PRSR(type) shared_ptr<IParser>((IParser*) DBG_NEW type())