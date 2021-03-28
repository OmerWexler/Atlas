#pragma once

#include "RejectNameMessage.h"
#include "RejectNameSerializer.h"

using namespace std;

string RejectNameSerializer::GetType() const
{
    return RejectNameMessage::TYPE;
}

string RejectNameSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    RejectNameMessage* ANMsg = (RejectNameMessage*) Message.get();

    string SMsg;
    SMsg += GetType();
    SMsg += ANMsg->GetInvalidName();
    
    return SMsg;
}