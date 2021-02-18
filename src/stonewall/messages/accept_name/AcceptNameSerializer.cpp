#pragma once

#include "AcceptNameMessage.h"
#include "AcceptNameSerializer.h"

using namespace std;

string AcceptNameSerializer::GetType() const
{
    return AcceptNameMessage::TYPE;
}

string AcceptNameSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    AcceptNameMessage* ANMsg = (AcceptNameMessage*) Message.get();

    string SMsg;
    SMsg += GetType();
    if (ANMsg->IsAccepted())
        SMsg += "1";
    else
        SMsg += "0";

    SMsg += ANMsg->GetInvalidName();
    
    return SMsg;
}