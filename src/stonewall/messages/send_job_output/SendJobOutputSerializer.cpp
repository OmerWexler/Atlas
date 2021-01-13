#pragma once

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
    return "SendJobOutput";
}

string SendJobOutputSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendJobOutputMessage* SJOMsg = (SendJobOutputMessage*) Message.get();
    SeperatorBasedMessage* SPBMsg = new SeperatorBasedMessage();

    SPBMsg->AddValue(SJOMsg->GetDescriptor());

    vector<Argument> Output = SJOMsg->GetOutput();
    for (int i = 0; i < Output.size(); i++)
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

ISerializer* SendJobOutputSerializer::Clone()
{
    return (ISerializer*) new SendJobOutputSerializer();
};