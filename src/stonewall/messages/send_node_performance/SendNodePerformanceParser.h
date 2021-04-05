#pragma once

#include "SeperatorBasedParser.h"
#include "IMessage.h"

using namespace std;

class SendNodePerformanceParser: public IParser
{
private:
    string HEADER = "SNP";
    SeperatorBasedParser SPBParser;

public:
    SendNodePerformanceParser();

    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};