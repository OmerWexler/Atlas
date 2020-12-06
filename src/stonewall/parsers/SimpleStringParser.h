#pragma once

#include "SimpleStringMessage.h"
#include "IMessage.h"
#include "IParser.h"

#include <string>

using namespace std;

class SimpleStringParser: IParser
{
public:
    virtual string GetType() const override
    {
        return "SimpleString";
    };

    virtual IMessage* Parse(const string& SMsg) override
    {
        return (IMessage*) new SimpleStringMessage(SMsg);
    };

    virtual bool CanParse(const string& SMsg) const override
    {
        return true;
    }

    virtual IParser* Clone() override
    {
        return (IParser*) new SimpleStringParser();
    };

    virtual ~SimpleStringParser() {};
};