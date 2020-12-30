#pragma once

#include "IMessage.h"
#include "ISerializer.h"

using namespace std;

class SendJobPolicySerializer: public ISerializer
{
private:
    static const string HEADER;

public:
    string GetType() const override;
    string Serialize(const IMessage* Message) const override;
    ISerializer* Clone() override;
};