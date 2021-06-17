#pragma once

#include "IMessage.h"
#include "ISerializer.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class TransferFileBlockSerializer: public ISerializer
{
private:
    string HEADER = "TFB";
    SeperatorBasedSerializer SPBSerializer;

public:
    TransferFileBlockSerializer();
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};