#pragma once

#include "IMessage.h"
#include "ISerializer.h"
#include "Logger.h"
#include "SeperatorBasedSerializer.h"

#include <string>

using namespace std;

class SendRSAKeySerializer: public ISerializer
{
private:
    SeperatorBasedSerializer SPBSerializer;

public:
    SendRSAKeySerializer();
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};