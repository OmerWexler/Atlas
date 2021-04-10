#pragma once

#include "Utils.h"
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

    string Type = Values[0];
    int Success = atoi(Values[1].c_str());
    string UniqueDecriptor = Values[2];
    string PathToTarget = move(Values[3]);

    Argument CurrentArg = Argument("", false);
    
    vector<Argument> Inputs = vector<Argument>();
    int NumOfInputs = atoi(Values[4].c_str());
    for (int i = 5; i < 5 + NumOfInputs * 2; i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Inputs.push_back(CurrentArg);
    }

    vector<Argument> Outputs = vector<Argument>();
    for (unsigned int i = 5 + NumOfInputs * 2; i < Values.size(); i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Outputs.push_back(CurrentArg);
    }

    shared_ptr<IJob> Job;
    JobRegistry::GetJob(Type, Job);
    Job->SetUniqueDescriptor(UniqueDecriptor);
    Job->SetSuccess(Success);
    Message.reset((IMessage*) DBG_NEW SendJobMessage(shared_ptr<IJob>(Job), Inputs, Path(PathToTarget), Outputs));
}

bool SendJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}