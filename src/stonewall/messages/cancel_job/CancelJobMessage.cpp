#pragma once

#include "CancelJobMessage.h"

using namespace std;

const string CancelJobMessage::TYPE = "CancelJob";

CancelJobMessage::CancelJobMessage(const string Descriptor)
{
    this->Descriptor = Descriptor;
}

string CancelJobMessage::GetType() const
{
    return TYPE;
}

string CancelJobMessage::GetDescriptor()
{
    return Descriptor;
}