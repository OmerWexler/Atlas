#pragma once

#include "IMessage.h"

using namespace std;

class CancelJobMessage: IMessage
{
private:
    string Descriptor = "";

public:
    const static string TYPE;
    
    CancelJobMessage(const string Descriptor);
    string GetType() const override;
    string GetDescriptor();
};