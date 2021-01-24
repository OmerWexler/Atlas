#pragma once

#include "Utils.h"
#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

RequestBestNodeSerializer::RequestBestNodeSerializer()
{
    SPBSerializer = SeperatorBasedSerializer();
}

string RequestBestNodeSerializer::GetType() const
{
    return RequestBestNodeMessage::TYPE;
};

string RequestBestNodeSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    string SMsg = HEADER;
    int Range = ((RequestBestNodeMessage*) Message.get())->GetRange();
    PCPerformance& MinimumPerformance = ((RequestBestNodeMessage*) Message.get())->GetMinimumAcceptablePerformance();

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SPBMsg->AddValue(to_string(Range));
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPUCores));
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPUFrequency));
    SPBMsg->AddValue(to_string(MinimumPerformance.CPUPerformance.CPULoad));

    unique_ptr<IMessage> USPBMsg((IMessage*) SPBMsg);
    SMsg += SPBSerializer.Serialize(USPBMsg);
    return SMsg;
};