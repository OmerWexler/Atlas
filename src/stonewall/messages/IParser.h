#pragma once

#include "IMessage.h"

#include <string>

using namespace std;

class IParser
{
public:
    virtual string GetType() = 0;
    virtual void Parse(string SMsg, IMessage& OutMessage) = 0;

};