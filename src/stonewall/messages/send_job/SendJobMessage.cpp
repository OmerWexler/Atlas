#pragma once

#include "SendJobMessage.h"

const string SendJobMessage::TYPE = "SendJob";

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, Path PathToTarget)
{
    this->Job = Job;
    this->Input = Input;
    this->PathToTarget = PathToTarget;
}

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output)
{
    this->Job = Job;
    this->Input = Input;
    this->Output = Output;
}

SendJobMessage::SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, Path PathToTarget, vector<Argument>& Output)
{
    this->Job = Job;
    this->Input = Input;
    this->PathToTarget = PathToTarget;
    this->Output = Output;
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

void SendJobMessage::SetPathToTarget(string StrPath)
{
    PathToTarget = Path(StrPath);
}

Path& SendJobMessage::GetPathToTarget()
{
    return PathToTarget;
}