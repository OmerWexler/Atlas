#pragma once

#include "SendJobSerializer.h"
#include "SendJobMessage.h"
#include "SeperatorBasedMessage.h"
#include "Argument.h"

using namespace std;

SendJobSerializer::SendJobSerializer()
{
    this->SPBSerializer = SeperatorBasedSerializer();
}

string SendJobSerializer::GetType() const
{
    return "SendJobPolicy";
}

string SendJobSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendJobMessage* SJMsg = (SendJobMessage*) Message.get();

    SeperatorBasedMessage* SPBMsg = new SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(SJMsg->GetJob()->GetType()));
    SPBMsg->AddValue(to_string(SJMsg->GetJob()->GetSuccess()));
    SPBMsg->AddValue(SJMsg->GetJob()->GetUniqueDescriptor());
    
    vector<Argument> Inputs = SJMsg->GetInput();
    for (Argument Input: Inputs)
    {
        SPBMsg->AddValue(Input.Value);
        if (Input.IsFile)
            SPBMsg->AddValue("1");
        else
            SPBMsg->AddValue("0");
    }

    string SMsg = "" + HEADER;
    SMsg += SPBSerializer.Serialize(unique_ptr<IMessage>((IMessage*) SPBMsg));

    return SMsg;
}

ISerializer* SendJobSerializer::Clone()
{
    return (ISerializer*) new SendJobSerializer();
}