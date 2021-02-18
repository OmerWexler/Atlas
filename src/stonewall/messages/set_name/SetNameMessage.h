#pragma once

#include "IMessage.h"

using namespace std;

class SetNameMessage: IMessage
{
private:
    string Name;
    
public:
    const static string TYPE;

    SetNameMessage(string Name);
    virtual string GetType() const override;
    virtual string GetName() const;
};