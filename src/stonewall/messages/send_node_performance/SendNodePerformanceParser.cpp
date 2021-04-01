#pragma once

#include "Utils.h"
#include "SendNodePerformanceParser.h"
#include "SeperatorBasedMessage.h"
#include "SendNodePerformanceMessage.h"

using namespace std;

SendNodePerformanceParser::SendNodePerformanceParser()
{
    SPBParser = SeperatorBasedParser();
}

string SendNodePerformanceParser::GetType() const
{
    return SendNodePerformanceMessage::TYPE;
}

void SendNodePerformanceParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    unique_ptr<IMessage> USPBMsg;
    SPBParser.Parse(SMsg.substr(HEADER.length()), USPBMsg);
    
    vector<string> Values = ((SeperatorBasedMessage*) USPBMsg.get())->GetValues();
    
    PCPerformance& Performance = PCPerformance();
    Performance.CPUPerformance.Cores = atoi(Values[0].c_str());
    Performance.CPUPerformance.FrequencyHZ = atoi(Values[1].c_str());
    Performance.CPUPerformance.CPULoad = atoi(Values[2].c_str());
    Performance.RAMPerformance.AvailablePhysicalBytes = atoi(Values[3].c_str());
    Performance.RAMPerformance.TotalPhysicalBytes = atoi(Values[4].c_str());
    Performance.RAMPerformance.MemoryLoad = atoi(Values[5].c_str());
    
    Message.reset(DBG_NEW SendNodePerformanceMessage(Performance));
}

bool SendNodePerformanceParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}