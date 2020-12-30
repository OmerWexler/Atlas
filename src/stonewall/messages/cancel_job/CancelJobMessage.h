#pragma once

#include "IMessage.h"

using namespace std;

class CancelJobMessage: IMessage
{
private:
    string Descriptor = "";

public:
    inline CancelJobMessage(const string Descriptor)
    {
        this->Descriptor = Descriptor;
    }

    inline string GetType() const override
    {
        return "CancelJob";
    };

    inline string GetDescriptor()
    {
        return Descriptor;
    }
};