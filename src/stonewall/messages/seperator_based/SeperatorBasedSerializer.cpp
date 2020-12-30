#pragma once

#include "SeperatorBasedMessage.h"
#include "SeperatorBasedSerializer.h"

using namespace std;

const string SeperatorBasedSerializer::SEPERATOR = "@@@";
const string SeperatorBasedSerializer::HEADER = "SEPB";

string SeperatorBasedSerializer::GetType() const
{
    return "SeperatorBased";
}

string SeperatorBasedSerializer::Serialize(const IMessage* Message) const
{
    SeperatorBasedMessage* SBMsg = (SeperatorBasedMessage*) Message;
    
    string SMsg = "";
    vector<string> Values = SBMsg->GetValues();
    SMsg += HEADER;
    if (Values.size() > 0)
    {
        SMsg += Values[0];

        for (int i = 1; i < Values.size(); i++)
        {
            SMsg += SEPERATOR + Values[i];
        }
    }

    return SMsg;
}

ISerializer* SeperatorBasedSerializer::Clone()
{
    return (ISerializer*) new SeperatorBasedSerializer();
}