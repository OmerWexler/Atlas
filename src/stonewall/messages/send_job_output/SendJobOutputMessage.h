#pragma once

#include <vector>

#include "IMessage.h"
#include "Argument.h"
#include "Path.h"

using namespace std;

class SendJobOutputMessage: IMessage
{
private:
    string Descriptor = "";
    vector<Argument> Output;
    Path PathToTarget;

public:
    const static string TYPE;

    SendJobOutputMessage(string Descriptor, Path& PathToTarget, vector<Argument>& Output);
    string GetType() const override;
    string GetDescriptor();
    vector<Argument>& GetOutput();
    Path& GetPathToTarget();
};