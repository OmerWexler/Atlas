#pragma once

#include <vector>
#include "IMessage.h"

using namespace std;

class SeperatorBasedMessage: public IMessage
{
private:
    vector<string> Values;

public:
    const static string TYPE;

    SeperatorBasedMessage();
    string GetType() const override;
    vector<string> GetValues();
    void AddValue(string Value);
};