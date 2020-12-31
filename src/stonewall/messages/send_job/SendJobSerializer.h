#pragma once

#include "IMessage.h"
#include "ISerializer.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class SendJobSerializer: public ISerializer
{
private:
    string HEADER = "SJ";
    SeperatorBasedSerializer SPBSerializer;

public:
    SendJobSerializer();
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
    ISerializer* Clone() override;
};