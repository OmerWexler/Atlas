#pragma once

#include "SendJobOutputMessage.h"

const string SendJobOutputMessage::TYPE = "SendJobOutput";

SendJobOutputMessage::SendJobOutputMessage(string Descriptor, Path PathToTarget, vector<Argument>& Output)
{
    this->Descriptor = Descriptor;
    this->Output = Output;
    this->PathToTarget = PathToTarget;
}

string SendJobOutputMessage::GetType() const
{
    return TYPE;
}

string SendJobOutputMessage::GetDescriptor()
{
    return Descriptor;
}

vector<Argument>& SendJobOutputMessage::GetOutput()
{
    return Output;
}

Path& SendJobOutputMessage::GetPathToTarget()
{
    return PathToTarget;
}