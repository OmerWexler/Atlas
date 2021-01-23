#pragma once

#include "SendBestNodeParser.h"
#include "SeperatorBasedMessage.h"
#include "SendBestNodeMessage.h"

using namespace std;

SendBestNodeParser::SendBestNodeParser()
{
    SPBParser = SeperatorBasedParser();
}

string SendBestNodeParser::GetType() const
{
    return SendBestNodeMessage::TYPE;
}

void SendBestNodeParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();
    
    PCPerformance& MinimumPerformance = PCPerformance();
    MinimumPerformance.CPUPerformance.CPUCores = atoi(Values[0].c_str());
    MinimumPerformance.CPUPerformance.CPUFrequency = atoi(Values[1].c_str());
    MinimumPerformance.CPUPerformance.CPULoad = atoi(Values[1].c_str());
    
    Message.reset(new SendBestNodeMessage(MinimumPerformance));
}

bool SendBestNodeParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}