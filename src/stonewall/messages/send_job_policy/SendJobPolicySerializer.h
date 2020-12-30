#pragma once

#include "IMessage.h"
#include "ISerializer.h"

using namespace std;

class SendJobPolicySerializer: public ISerializer
{
private:
    string HEADER = "SJP";

public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
    ISerializer* Clone() override;
};