#pragma once

#include "CancelJobMessage.h"

using namespace std;

const string CancelJobMessage::TYPE = "CancelJob";

CancelJobMessage::CancelJobMessage(const string Descriptor, string PathToTarget)
{
    this->Descriptor = Descriptor;
    this->PathToTarget = Path(PathToTarget);
}

string CancelJobMessage::GetType() const
{
    return TYPE;
}

Path& CancelJobMessage::GetPathToTarget()
{
    return PathToTarget;
}

string CancelJobMessage::GetDescriptor()
{
    return Descriptor;
}