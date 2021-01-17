#pragma once

#include "ISerializer.h"
#include "IMessage.h"

using namespace std;

class CancelJobSerializer: ISerializer
{
private:
    string HEADER = "CJ";

public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};