#pragma once

#include "IMessage.h"
#include "SeperatorBasedParser.h"

using namespace std;

class SendJobParser: public IParser
{
private:
    string HEADER = "SJ";
    SeperatorBasedParser SPBParser;

public:
    SendJobParser();
    
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};