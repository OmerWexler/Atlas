#pragma once

#include "Utils.h"
#include "SendJobOutputParser.h"
#include "SendJobOutputMessage.h"

#include "SeperatorBasedParser.h"
#include "SeperatorBasedMessage.h"

using namespace std;

SendJobOutputParser::SendJobOutputParser()
{
    SPBParser = SeperatorBasedParser();
}

string SendJobOutputParser::GetType() const
{
    return SendJobOutputMessage::TYPE;
}

void SendJobOutputParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();
    
    string Descriptor = Values[0];
    string PathToTarget = Values[1];

    Argument CurrentArg = Argument();
    vector<Argument> Outputs = vector<Argument>();
    for (unsigned int i = 2; i < Values.size(); i += 2)
    {
        CurrentArg.Value = Values[i];
        CurrentArg.IsFile = Values[i + 1] == "1";

        Outputs.push_back(CurrentArg);
    }

    Message.reset((IMessage*) DBG_NEW SendJobOutputMessage(Descriptor, Path(PathToTarget), Outputs));
}

bool SendJobOutputParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
        SPBParser.CanParse(SMsg.substr(HEADER.length()));
}