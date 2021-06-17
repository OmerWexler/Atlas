#pragma once

#include "IMessage.h"
#include "SeperatorBasedParser.h"

using namespace std;

class TransferFileBlockParser: public IParser
{
private:
    string HEADER = "TFB";
    SeperatorBasedParser SPBParser;

public:
    TransferFileBlockParser();
    
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};