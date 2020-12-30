#pragma once

#include "IParser.h"
#include "IMessage.h"

using namespace std;

class CancelJobParser: public IParser
{
private:
    static const string HEADER;

public:
    string GetType() const override;
    IMessage* Parse(const string& SMsg) override;
    bool CanParse(const string& SMsg) const override;
    IParser* Clone() override;
};