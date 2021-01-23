#pragma once

#include "IMessage.h"

using namespace std;

class SimpleStringMessage: IMessage
{
private:
    string Value;
    
public:
    const static string TYPE;

    SimpleStringMessage(string Value);
    virtual string GetType() const override;
    virtual string GetValue() const;
};