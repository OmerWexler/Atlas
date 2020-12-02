#pragma once

#include "SimpleStringMessage.h"
#include "IMessage.h"
#include "IParser.h"

#include <string>

using namespace std;

class SimpleStringParser: IParser
{
public:
    virtual string GetType() const
    {
        return "SimpleString";
    };

    virtual IMessage* Parse(const string& SMsg)
    {
        return (IMessage*) new SimpleStringMessage(SMsg);
    };

    virtual bool CanParse(const string& SMsg) const
    {
        return true;
    }
};