#pragma once

#include "IMessage.h"
#include "IParser.h"

using namespace std;

class SimpleStringParser: IParser
{
public:
    string GetType() const override;
    IMessage* Parse(const string& SMsg) override;
    bool CanParse(const string& SMsg) const override;
    IParser* Clone() override;
};