#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class RequestBestNodeSerializer: public ISerializer
{
private:
    string HEADER = "RBN";
    SeperatorBasedSerializer SPBSerializer;

public:
    RequestBestNodeSerializer();
    
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
    ISerializer* Clone() override;
};