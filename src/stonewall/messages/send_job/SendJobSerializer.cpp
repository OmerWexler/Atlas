#pragma once

#include "Utils.h"
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
    return SendJobMessage::TYPE;
}

string SendJobSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SendJobMessage* SJMsg = (SendJobMessage*) Message.get();

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(SJMsg->GetJob()->GetType()));
    SPBMsg->AddValue(to_string(SJMsg->GetJob()->GetSuccess()));
    SPBMsg->AddValue(SJMsg->GetJob()->GetUniqueDescriptor());
    
    vector<Argument> Inputs = SJMsg->GetInput();
    SPBMsg->AddValue(to_string(Inputs.size()));
    for (Argument Input: Inputs)
    {
        SPBMsg->AddValue(Input.Value);
        if (Input.IsFile)
            SPBMsg->AddValue("1");
        else
            SPBMsg->AddValue("0");
    }

    vector<Argument> Outputs = SJMsg->GetOutput();
    for (Argument Output: Outputs)
    {
        SPBMsg->AddValue(Output.Value);
        if (Output.IsFile)
            SPBMsg->AddValue("1");
        else
            SPBMsg->AddValue("0");
    }

    string SMsg = "" + HEADER;
    SMsg += SPBSerializer.Serialize(unique_ptr<IMessage>((IMessage*) SPBMsg));

    return SMsg;
}