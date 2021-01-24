#include "Utils.h"
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
    
    RequestBestNodeMessage* Msg = DBG_NEW RequestBestNodeMessage(5, Performance);
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "RBNSEPB5@@@20@@@20@@@20")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (RequestBestNodeMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    if (Msg->GetRange() != 5 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPUCores != 20 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPUFrequency != 20 ||
        Msg->GetMinimumAcceptablePerformance().CPUPerformance.CPULoad != 20)
    {
        return -1;
    }

    return 0;
}
