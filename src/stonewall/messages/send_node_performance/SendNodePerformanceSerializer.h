#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class SendNodePerformanceSerializer: public ISerializer
{
private:
    string HEADER = "SNP";
    SeperatorBasedSerializer SPBSerializer;

public:
    SendNodePerformanceSerializer();
    
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};