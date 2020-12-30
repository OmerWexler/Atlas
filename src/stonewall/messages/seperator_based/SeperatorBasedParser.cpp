#pragma once

#include "SeperatorBasedParser.h"
#include "SeperatorBasedMessage.h"

using namespace std;

const string SeperatorBasedParser::SEPERATOR = "@@@";
const string SeperatorBasedParser::HEADER = "SEPB";

string SeperatorBasedParser::GetType() const
{
    return "SeperatorBased";
}

IMessage* SeperatorBasedParser::Parse(const string& SMsg)
{
    SeperatorBasedMessage* Msg = new SeperatorBasedMessage();
    
    string Section = "";
    for (size_t i = HEADER.length(); i < SMsg.length(); i++)
    {
        Section += SMsg.substr(i, 1);

        if (i + SEPERATOR.length() < SMsg.length())
        {
            if (SMsg.substr(i + 1, SEPERATOR.length()) == SEPERATOR)
            {
                Msg->AddValue(Section);
                Section = "";
                i += SEPERATOR.length();
            }
        }
    }

    Msg->AddValue(Section);

    return (IMessage*) Msg;
}

bool SeperatorBasedParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}

IParser* SeperatorBasedParser::Clone()
{
    return (IParser*) new SeperatorBasedParser();
}