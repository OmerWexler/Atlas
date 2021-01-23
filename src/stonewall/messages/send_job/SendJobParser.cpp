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
    return SendJobMessage::TYPE;
}

void SendJobParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();

    int TYPE = atoi(Values[0].c_str());
    int Success = atoi(Values[1].c_str());
    string UniqueDecriptor = Values[2];

    Argument CurrentArg = Argument("", false);
    
    vector<Argument> Inputs = vector<Argument>();
    int NumOfInputs = atoi(Values[3].c_str());
    for (int i = 4; i < 4 + NumOfInputs * 2; i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Inputs.push_back(CurrentArg);
    }

    vector<Argument> Outputs = vector<Argument>();
    for (int i = 4 + NumOfInputs * 2; i < Values.size(); i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Outputs.push_back(CurrentArg);
    }

    shared_ptr<IJob> Job;
    JobRegistry::GetJob(TYPE, Job);
    Job->SetUniqueDescriptor(UniqueDecriptor);
    Job->SetSuccess(Success);
    Message.reset((IMessage*) new SendJobMessage(shared_ptr<IJob>(Job), Inputs, Outputs));
}

bool SendJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}