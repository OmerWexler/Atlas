#pragma once

#include "SendBestNodeSerializer.h"
#include "SendBestNodeMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

SendBestNodeSerializer::SendBestNodeSerializer()
{
    SPBSerializer = SeperatorBasedSerializer();
}

string SendBestNodeSerializer::GetType() const
{
    return "SendBestNode";
};

string SendBestNodeSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER;
    PCPerformance& Performance = ((SendBestNodeMessage*) Message.get())->GetNodePerformance();

    SeperatorBasedMessage* SPBMsg = new SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.CPUCores));
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.CPUFrequency));
    SPBMsg->AddValue(to_string(Performance.CPUPerformance.CPULoad));

    unique_ptr<IMessage> USPBMsg((IMessage*) SPBMsg);
    SMsg += SPBSerializer.Serialize(USPBMsg);
    return SMsg;
};