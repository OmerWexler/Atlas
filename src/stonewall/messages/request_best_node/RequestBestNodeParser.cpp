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
    
    SeperatorBasedMessage* SPBMsg = (SeperatorBasedMessage*) USPBMsg.get();
    int Range = atoi(SPBMsg->GetValues()[0].c_str());
    
    PCPerformance& MinimumPerformance = PCPerformance();
    MinimumPerformance.CPUPerformance.CPUCores = atoi(SPBMsg->GetValues()[1].c_str());
    MinimumPerformance.CPUPerformance.CPUFrequency = atoi(SPBMsg->GetValues()[2].c_str());
    MinimumPerformance.CPUPerformance.CPULoad = atoi(SPBMsg->GetValues()[2].c_str());
    
    Message.reset(new RequestBestNodeMessage(Range, MinimumPerformance));
}

bool RequestBestNodeParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}

IParser* RequestBestNodeParser::Clone()
{
    return (IParser*) new RequestBestNodeParser();
}