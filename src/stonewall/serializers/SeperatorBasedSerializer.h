#pragma once

#include "IMessage.h"
#include "SeperatorBasedMessage.h"
#include "ISerializer.h"
#include "Logger.h"

#include <string>

using namespace std;

class SeperatorBasedSerializer: ISerializer
{
private:
    const string SEPERATOR = "@@@";
    const string HEADER = "SEPB";

public:
    virtual string GetType() const
    {
        return "SeperatorBased";
    };

    virtual string Serialize(const IMessage* Message) const
    {
        if (Message->GetType() != GetType())
        {
            Logger::GetInstance().Error("Message of type - " + Message->GetType() + 
                                        " cannot be serialized by serializer of type - " + GetType());
            
            return "";
        }
        SeperatorBasedMessage* SBMsg = (SeperatorBasedMessage*) Message;
        
        string SMsg = "";
        SMsg += HEADER;
        
        for (string Value: SBMsg->GetValues())
        {
            SMsg += Value + SEPERATOR;
        }

        return SMsg;
    };

    virtual ISerializer* Clone() override
    {
        return (ISerializer*) new SeperatorBasedSerializer();
    };
};