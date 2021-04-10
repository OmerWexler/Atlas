#pragma once

#include "Utils.h"
#include "SendJobOutputSerializer.h"
#include "SendJobOutputMessage.h"

#include "SeperatorBasedMessage.h"
#include "SeperatorBasedSerializer.h"

SendJobOutputSerializer::SendJobOutputSerializer()
{
    Serializer = SeperatorBasedSerializer();
}

string SendJobOutputSerializer::GetType() const
{
    return SendJobOutputMessage::TYPE;
}

string SendJobOutputSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendJobOutputMessage* SJOMsg = (SendJobOutputMessage*) Message.get();
    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();

    SPBMsg->AddValue(SJOMsg->GetDescriptor());
    SPBMsg->AddValue(SJOMsg->GetPathToTarget().GetStrPath());

    vector<Argument> Output = SJOMsg->GetOutput();
    for (unsigned int i = 0; i < Output.size(); i++)
    {
        SPBMsg->AddValue(Output[i].Value);
        if (Output[i].IsFile)
            SPBMsg->AddValue("1");
        else
            SPBMsg->AddValue("0");
    }

    string SMsg = HEADER + Serializer.Serialize(unique_ptr<IMessage>((IMessage*) SPBMsg));
    return SMsg;
};