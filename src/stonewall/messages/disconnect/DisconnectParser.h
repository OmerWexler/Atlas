#pragma once

#include "IParser.h"
#include "IMessage.h"

using namespace std;

class DisconnectParser: public IParser
{
private:
    string HEADER = "DC";

public:
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};