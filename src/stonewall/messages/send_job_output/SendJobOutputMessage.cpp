#pragma once

#include "SendJobOutputMessage.h"

const string SendJobOutputMessage::TYPE = "SendJobOutput";

SendJobOutputMessage::SendJobOutputMessage(string Descriptor, vector<Argument>& Output)
{
    this->Descriptor = Descriptor;
    this->Output = Output;
}

string SendJobOutputMessage::GetType() const
{
    return TYPE;
}

string SendJobOutputMessage::GetDescriptor()
{
    return Descriptor;
}

vector<Argument> SendJobOutputMessage::GetOutput()
{
    return Output;
}