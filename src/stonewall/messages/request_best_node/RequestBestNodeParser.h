#pragma once

#include "SeperatorBasedParser.h"
#include "IMessage.h"

using namespace std;

class RequestBestNodeParser: public IParser
{
private:
    static const string HEADER;
    SeperatorBasedParser SPBParser;

public:
    RequestBestNodeParser();

    string GetType() const override;
    IMessage* Parse(const string& SMsg) override;
    bool CanParse(const string& SMsg) const override;
    IParser* Clone() override;
};