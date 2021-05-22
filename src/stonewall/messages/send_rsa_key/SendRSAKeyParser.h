#pragma once

#include "IMessage.h"
#include "IParser.h"
#include "SeperatorBasedParser.h"

using namespace std;

class SendRSAKeyParser: IParser
{
private:
    SeperatorBasedParser SPBParser;
public:
    SendRSAKeyParser();
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};