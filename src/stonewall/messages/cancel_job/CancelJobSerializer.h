#pragma once

#include "ISerializer.h"
#include "IMessage.h"

using namespace std;

class CancelJobSerializer: ISerializer
{
private:
    static const string HEADER;

public:
    string GetType() const override;
    string Serialize(const IMessage* Message) const override;
    ISerializer* Clone() override;
};