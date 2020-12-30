#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class RequestBestNodeSerializer: public ISerializer
{
private:
    static const string HEADER;
    SeperatorBasedSerializer SPBSerializer;

public:
    RequestBestNodeSerializer();
    
    string GetType() const override;
    string Serialize(const IMessage* Message) const override;
    ISerializer* Clone() override;
};