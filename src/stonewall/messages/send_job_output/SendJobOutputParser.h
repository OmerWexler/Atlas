#pragma once

#include "IParser.h"
#include "IMessage.h"
#include "SeperatorBasedParser.h"

using namespace std;

class SendJobOutputParser: public IParser
{
private:
    string HEADER = "SJO";
    SeperatorBasedParser SPBParser;

public:
    SendJobOutputParser();

    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
    IParser* Clone() override;
};