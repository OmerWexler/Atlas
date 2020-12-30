#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "PCPerformance.h"

using namespace std;

int TestRequestBestNodeMessages() 
{
    RequestBestNodeParser Parser = RequestBestNodeParser();
    RequestBestNodeSerializer Serializer = RequestBestNodeSerializer();

    PCPerformance Performance = PCPerformance();
    Performance.CPUPerformance.CPUCores = 20;
    Performance.CPUPerformance.CPUFrequency = 20;
    Performance.CPUPerformance.CPULoad = 20;
    
    RequestBestNodeMessage* Msg = new RequestBestNodeMessage(5, Performance);

    string SMsg = Serializer.Serialize((IMessage*)Msg);
    if (SMsg != "RBNSEPB5@@@20@@@20@@@20")
    {
        delete Msg;
        return -1;
    }

    if (Parser.CanParse(SMsg))
        Msg = (RequestBestNodeMessage*) Parser.Parse(SMsg);
    else 
    {
        delete Msg;
        return -1;
    }

    if (Msg->GetRange() != 5 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPUCores != 20 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPUFrequency != 20 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPULoad != 20)
    {
        delete Msg;
        return -1;
    }

    delete Msg;
    return 0;
}
