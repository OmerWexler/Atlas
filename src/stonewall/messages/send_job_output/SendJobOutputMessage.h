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
    const static string TYPE;

    SendJobOutputMessage(string Descriptor, vector<Argument>& Output);
    string GetType() const override;
    string GetDescriptor();
    vector<Argument> GetOutput();
};