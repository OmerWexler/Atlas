#pragma once

#include "SeperatorBasedMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

string SeperatorBasedSerializer::GetType() const
{
    return SeperatorBasedMessage::TYPE;
}

string SeperatorBasedSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    SeperatorBasedMessage* SBMsg = (SeperatorBasedMessage*) Message.get();
    
    string SMsg = "";
    vector<string> Values = SBMsg->GetValues();
    SMsg += HEADER;
    if (Values.size() > 0)
    {
        SMsg += Values[0];

        for (unsigned int i = 1; i < Values.size(); i++)
        {
            SMsg += SEPERATOR + Values[i];
        }
    }

    return SMsg;
}