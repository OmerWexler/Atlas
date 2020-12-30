#pragma once

#include "RequestBestNodeParser.h"
#include "SeperatorBasedMessage.h"
#include "RequestBestNodeMessage.h"

using namespace std;

const string RequestBestNodeParser::HEADER = "RBN";

RequestBestNodeParser::RequestBestNodeParser()
{
    SPBParser = SeperatorBasedParser();
}

string RequestBestNodeParser::GetType() const
{
    return "RequestBestNode";
}

IMessage* RequestBestNodeParser::Parse(const string& SMsg)
{
    SeperatorBasedMessage* SPBMsg = (SeperatorBasedMessage*) SPBParser.Parse(SMsg.substr(HEADER.length()));
    
    int Range = atoi(SPBMsg->GetValues()[0].c_str());
    
    PCPerformance& MinimumPerformance = PCPerformance();
    MinimumPerformance.CPUPerformance.CPUCores = atoi(SPBMsg->GetValues()[1].c_str());
    MinimumPerformance.CPUPerformance.CPUFrequency = atoi(SPBMsg->GetValues()[2].c_str());
    MinimumPerformance.CPUPerformance.CPULoad = atoi(SPBMsg->GetValues()[2].c_str());
    
    return new RequestBestNodeMessage(Range, MinimumPerformance);
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