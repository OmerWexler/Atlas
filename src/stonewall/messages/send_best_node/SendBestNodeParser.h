#pragma once

#include "SeperatorBasedParser.h"
#include "IMessage.h"

using namespace std;

class SendBestNodeParser: public IParser
{
private:
    string HEADER = "RBN";
    SeperatorBasedParser SPBParser;

public:
    SendBestNodeParser();

    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};