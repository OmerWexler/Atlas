#pragma once

#include <string>
#include <memory>

#include "IMessage.h"
#include "SendJobPolicyMessage.h"

using namespace std;

class SendJobPolicyParser: public ISerializer
{
private:
    const string HEADER = "SJP";

public:
    inline virtual string GetType() const
    {
        return "SendJobPolicy"
    }

    inline virtual IMessage* Parse(const string& SMsg)
    {
        bool AcceptJobs = SMsg.substr(SMsg.length() - 1) == "1";
        return (IMessage*) new SendJobPolicyMessage(AcceptJobs);
    }

    inline virtual bool CanParse(const string& SMsg) const
    {
        return SMsg.substr(0, HEADER.length()) == HEADER;
    }
    
    inline virtual IParser* Clone()
    {
        return (IParser*) new SendJobPolicyParser();
    }
};