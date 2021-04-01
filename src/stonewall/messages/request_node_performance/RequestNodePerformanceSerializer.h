#pragma once

#include "IMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

class RequestNodePerformanceSerializer: public ISerializer
{
private:
    string HEADER = "RBN";

public:
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};