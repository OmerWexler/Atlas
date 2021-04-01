#pragma once

#include "Utils.h"
#include "SendNodePerformanceSerializer.h"
#include "SendNodePerformanceMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

SendNodePerformanceSerializer::SendNodePerformanceSerializer()
{
    SPBSerializer = SeperatorBasedSerializer();
}

string SendNodePerformanceSerializer::GetType() const
{
    return SendNodePerformanceMessage::TYPE;
};

string SendNodePerformanceSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER + "";
    PCPerformance& Performance = ((SendNodePerformanceMessage*) Message.get())->GetNodePerformance();

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.Cores));
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.FrequencyHZ));
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.CPULoad));
    SPBMsg->AddValue(to_string(Performance.RAMPerformance.AvailablePhysicalBytes));
    SPBMsg->AddValue(to_string(Performance.RAMPerformance.TotalPhysicalBytes));
    SPBMsg->AddValue(to_string(Performance.RAMPerformance.MemoryLoad));

    unique_ptr<IMessage> USPBMsg((IMessage*) SPBMsg);
    SMsg += SPBSerializer.Serialize(USPBMsg);
    return SMsg;
};