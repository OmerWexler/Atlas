#pragma once

#include "RequestBestNodeParser.h"
#include "SeperatorBasedMessage.h"
#include "RequestBestNodeMessage.h"

using namespace std;

RequestBestNodeParser::RequestBestNodeParser()
{
    SPBParser = SeperatorBasedParser();
}

string RequestBestNodeParser::GetType() const
{
    return "RequestBestNode";
}

void RequestBestNodeParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();
    int Range = atoi(Values[0].c_str());
    
    PCPerformance& MinimumPerformance = PCPerformance();
    MinimumPerformance.CPUPerformance.CPUCores = atoi(Values[1].c_str());
    MinimumPerformance.CPUPerformance.CPUFrequency = atoi(Values[2].c_str());
    MinimumPerformance.CPUPerformance.CPULoad = atoi(Values[2].c_str());
    
    Message.reset(new RequestBestNodeMessage(Range, MinimumPerformance));
}

bool RequestBestNodeParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}