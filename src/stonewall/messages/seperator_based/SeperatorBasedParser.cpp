#pragma once

#include "Utils.h"
#include "SeperatorBasedParser.h"
#include "SeperatorBasedMessage.h"

using namespace std;

string SeperatorBasedParser::GetType() const
{
    return SeperatorBasedMessage::TYPE;
}

void SeperatorBasedParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    
    string Section = "";
    for (size_t i = HEADER.length(); i < SMsg.length(); i++)
    {
        Section += SMsg.substr(i, 1);

        if (i + SEPERATOR.length() < SMsg.length())
        {
            if (SMsg.substr(i + 1, SEPERATOR.length()) == SEPERATOR)
            {
                SPBMsg->AddValue(Section);
                Section = "";
                i += SEPERATOR.length();
            }
        }
    }

    SPBMsg->AddValue(Section);
    Message.reset((IMessage*) SPBMsg);
}

bool SeperatorBasedParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}