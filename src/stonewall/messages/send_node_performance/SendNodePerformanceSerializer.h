#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class SendNodePerformanceSerializer: public ISerializer
{
private:
    string HEADER = "RBN";
    SeperatorBasedSerializer SPBSerializer;

public:
    SendNodePerformanceSerializer();
    
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};