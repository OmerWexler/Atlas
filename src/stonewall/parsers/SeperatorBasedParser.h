#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "IParser.h"
#include "SeperatorBasedMessage.h"

using namespace std;

class SeperatorBasedParser: public IParser
{
private:
    const string SEPERATOR = "@@@";
    const string HEADER = "SEPB";

public:
    inline virtual string GetType() const
    {
        return "SeperatorBased";
    }
    
    inline virtual IMessage* Parse(const string& SMsg)
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
    
    inline virtual bool CanParse(const string& SMsg) const
    {
        return SMsg.substr(0, HEADER.length()) == HEADER;
    }
    
    inline virtual IParser* Clone()
    {
        return new SeperatorBasedParser();
    }
};