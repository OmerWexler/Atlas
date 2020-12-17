#pragma once

#include <string>
#include <vector>

#include "IMessage.h"

using namespace std;

class SeperatorBasedMessage: IMessage
{
private:
    vector<string> Values;

public:
    inline SeperatorBasedMessage()
    {
        this->Values = vector<string>();
    }

    inline virtual string GetType() const override
    {
        return "SeperatorBased";
    }

    inline vector<string> GetValues()
    {
        return Values;
    }

    inline void AddValue(string Value)
    {
        Values.push_back(Value);
    }
};