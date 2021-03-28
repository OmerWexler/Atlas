#pragma once

#include "RejectNameMessage.h"

using namespace std;

const string RejectNameMessage::TYPE = "RejectName"; 

RejectNameMessage::RejectNameMessage(string Name)
{
    this->Name = Name;
}

string RejectNameMessage::GetType() const
{
    return TYPE;
}

string RejectNameMessage::GetInvalidName() const
{
    return Name;
}
