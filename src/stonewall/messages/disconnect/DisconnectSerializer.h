#pragma once

#include "ISerializer.h"
#include "IMessage.h"

using namespace std;

class DisconnectSerializer: ISerializer
{
private:
    string HEADER = "DC";

public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};