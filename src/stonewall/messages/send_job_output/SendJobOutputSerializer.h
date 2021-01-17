#pragma once

#include "SeperatorBasedSerializer.h"
#include "ISerializer.h"
#include "IMessage.h"

using namespace std;

class SendJobOutputSerializer: ISerializer
{
private:
    string HEADER = "SJO";
    SeperatorBasedSerializer Serializer;

public:
    SendJobOutputSerializer();
    
    string GetType() const override;
    string Serialize(const unique_ptr<IMessage>& Message) const override;
};