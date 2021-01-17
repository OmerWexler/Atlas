#pragma once

#include "IMessage.h"
#include "ISerializer.h"

using namespace std;

class SeperatorBasedSerializer: public ISerializer
{
private:
    string SEPERATOR = "@@@";
    string HEADER = "SEPB";

public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};