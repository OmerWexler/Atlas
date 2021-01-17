#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "IParser.h"

using namespace std;

class SeperatorBasedParser: public IParser
{
private:
    string SEPERATOR = "@@@";
    string HEADER = "SEPB";

public:
    string GetType() const override;
    void Parse(const string& SMsg, unique_ptr<IMessage>& Message) override;
    bool CanParse(const string& SMsg) const override;
};