#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "Cloneable.h"

using namespace std;

class IParser: public Cloneable<IParser*>
{
public:
    virtual string GetType() const = 0;
    virtual void Parse(const string& SMsg, unique_ptr<IMessage>& Message) = 0;
    virtual bool CanParse(const string& SMsg) const = 0;
    
    virtual ~IParser() {};
};