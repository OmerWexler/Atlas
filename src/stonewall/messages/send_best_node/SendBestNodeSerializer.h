#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class SendBestNodeSerializer: public ISerializer
{
private:
    string HEADER = "RBN";
    SeperatorBasedSerializer SPBSerializer;

public:
    SendBestNodeSerializer();
    
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};