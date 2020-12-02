#pragma once

#include "IMessage.h"

#include <string>

using namespace std;

class IParser
{
public:
    virtual string GetType() const = 0;
    virtual IMessage* Parse(const string& SMsg) = 0;
    virtual bool CanParse(const string& SMsg) const = 0;

    virtual ~IParser() {};
};