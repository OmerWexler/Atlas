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
    PCPerformance& MinimumPerformance = ((SendBestNodeMessage*) Message.get())->GetMinimumAcceptablePerformance();

    SeperatorBasedMessage* SPBMsg = new SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPUCores));
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPUFrequency));
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPULoad));

    unique_ptr<IMessage> USPBMsg((IMessage*) SPBMsg);
    SMsg += SPBSerializer.Serialize(USPBMsg);
    return SMsg;
};

ISerializer* SendBestNodeSerializer::Clone()
{
    return (ISerializer*) new SendBestNodeSerializer();
}