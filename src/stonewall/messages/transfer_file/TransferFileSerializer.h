#pragma once

#include "IMessage.h"
#include "ISerializer.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class TransferFileSerializer: public ISerializer
{
private:
    string HEADER = "TF";
    SeperatorBasedSerializer SPBSerializer;

public:
    TransferFileSerializer();
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};