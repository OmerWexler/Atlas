#pragma once

#include "IMessage.h"
#include "IParser.h"

using namespace std;

class AcceptNameParser: IParser
{
public:
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};