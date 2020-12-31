#pragma once

#include "SendJobParser.h"
#include "SendJobMessage.h"
#include "SeperatorBasedMessage.h"
#include "JobRegistry.h"

using namespace std;

SendJobParser::SendJobParser()
{
    SPBParser = SeperatorBasedParser();
}

string SendJobParser::GetType() const
{
    return "SendJobPolicy";
}

void SendJobParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();

    int Type = atoi(Values[0].c_str());
    int Success = atoi(Values[1].c_str());
    string UniqueDecriptor = Values[2];

    vector<Argument> Inputs = vector<Argument>();
    Argument CurrentArg = Argument("", false);
    for (int i = 3; i < Values.size(); i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Inputs.push_back(CurrentArg);
    }

    IJob* Job = JobRegistry::GetJob(Type, Success, UniqueDecriptor);
    Message.reset((IMessage*) new SendJobMessage(Job, Inputs));
}

bool SendJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}

IParser* SendJobParser::Clone()
{
    return (IParser*) new SendJobParser();
}