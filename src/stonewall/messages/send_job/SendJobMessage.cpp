#pragma once

#include "SendJobMessage.h"

const string SendJobMessage::TYPE = "SendJob";

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input)
{
    this->Job = Job;
    this->Input = Input;
}

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output)
{
    this->Job = Job;
    this->Input = Input;
    this->Output = Output;
}

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output, string TargetNodePath)
{
    this->Job = Job;
    this->Input = Input;
    this->Output = Output;
    this->TargetNodePath = Path(TargetNodePath);
}

string SendJobMessage::GetType() const
{
    return TYPE;
}

shared_ptr<IJob>& SendJobMessage::GetJob()
{
    return Job;
}

vector<Argument> SendJobMessage::GetInput() const
{
    return Input;
}

void SendJobMessage::SetOutput(vector<Argument> Output)
{
    this->Output = Output;
}

vector<Argument> SendJobMessage::GetOutput() const
{
    return Output;
}

void SendJobMessage::SetTargetPath(string StrPath)
{
    TargetNodePath = Path(StrPath);
}

Path& SendJobMessage::GetTargetPath()
{
    return TargetNodePath;
}