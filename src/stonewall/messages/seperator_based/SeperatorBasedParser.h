#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "IParser.h"

using namespace std;

class SeperatorBasedParser: public IParser
{
private:
    static const string SEPERATOR;
    static const string HEADER;

public:
    string GetType() const override;
    IMessage* Parse(const string& SMsg) override;
    bool CanParse(const string& SMsg) const override;
    IParser* Clone() override;
};