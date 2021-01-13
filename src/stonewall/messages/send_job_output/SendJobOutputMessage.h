#pragma once

#include <vector>

#include "IMessage.h"
#include "Argument.h"

using namespace std;

class SendJobOutputMessage: IMessage
{
private:
    string Descriptor = "";
    vector<Argument> Output;

public:
    inline SendJobOutputMessage(string Descriptor, vector<Argument>& Output)
    {
        this->Descriptor = Descriptor;
        this->Output = Output;
    }

    inline string GetType() const override
    {
        return "SendJobOutput";
    };

    inline string GetDescriptor()
    {
        return Descriptor;
    }

    inline vector<Argument> GetOutput()
    {
        return Output;
    }
};