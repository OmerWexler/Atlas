#pragma once

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

const string RequestBestNodeSerializer::HEADER = "RBN";

RequestBestNodeSerializer::RequestBestNodeSerializer()
{
    SPBSerializer = SeperatorBasedSerializer();
}

string RequestBestNodeSerializer::GetType() const
{
    return "RequestBestNode";
};

string RequestBestNodeSerializer::Serialize(const IMessage* Message) const
{
    string SMsg = HEADER;
    int Range = ((RequestBestNodeMessage*) Message)->GetRange();
    PCPerformance& MinimumPerformance = ((RequestBestNodeMessage*) Message)->GetMinimumAcceptablePerformance();
    SeperatorBasedMessage SPBMsg = SeperatorBasedMessage();

    SPBMsg.AddValue(to_string(Range));
    SPBMsg.AddValue(to_string(MinimumPerformance.CPUPerformance.CPUCores));
    SPBMsg.AddValue(to_string(MinimumPerformance.CPUPerformance.CPUFrequency));
    SPBMsg.AddValue(to_string(MinimumPerformance.CPUPerformance.CPULoad));

    SMsg += SPBSerializer.Serialize((IMessage*) &SPBMsg);
    return SMsg;
};

ISerializer* RequestBestNodeSerializer::Clone()
{
    return (ISerializer*) new RequestBestNodeSerializer();
}