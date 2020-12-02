#pragma once

#include "IMessage.h"
#include <string>

using namespace std;

class SimpleStringMessage: IMessage
{
private:
    string Value;
    
public:
    SimpleStringMessage(string Value)
    {
        this->Value = Value;
    }

    virtual string GetType() const
    {
        return "SimpleString";
    };

    virtual string GetValue() const
    {
        return Value;
    };
};