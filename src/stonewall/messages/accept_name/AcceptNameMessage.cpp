#pragma once

#include "AcceptNameMessage.h"

using namespace std;

const string AcceptNameMessage::TYPE = "AcceptName"; 

AcceptNameMessage::AcceptNameMessage(bool Accepted, string Name)
{
    this->Accepted = Accepted;
    this->Name = Name;
}

string AcceptNameMessage::GetType() const
{
    return TYPE;
}

bool AcceptNameMessage::IsAccepted() const
{
    return Accepted;
}

string AcceptNameMessage::GetInvalidName() const
{
    return Name;
}
