#pragma once

#include <sstream>

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
    Path NodePath = Path(Values[0]);
    
    PCPerformance Performance = PCPerformance();
    istringstream iss;
    Performance.CPUPerformance.Cores = atoi(Values[1].c_str());

    iss = istringstream(Values[2]);
    iss >> Performance.CPUPerformance.FrequencyHZ;

    Performance.CPUPerformance.CPULoad = atoi(Values[3].c_str());

    iss = istringstream(Values[4]);
    iss >> Performance.RAMPerformance.AvailablePhysicalBytes;

    iss = istringstream(Values[5]);
    iss >> Performance.RAMPerformance.TotalPhysicalBytes;

    Performance.RAMPerformance.MemoryLoad = atoi(Values[6].c_str());
    
    Message.reset(DBG_NEW SendNodePerformanceMessage(Performance, NodePath));
}

bool SendNodePerformanceParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER &&
            SPBParser.CanParse(SMsg.substr(HEADER.length()));
}