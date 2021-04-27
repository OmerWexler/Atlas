#include "Utils.h"
#include "SendNodePerformanceSerializer.h"
#include "SendNodePerformanceParser.h"
#include "SendNodePerformanceMessage.h"
#include "PCPerformance.h"

using namespace std;

int TestSendNodePerformanceMessages() 
{
    SendNodePerformanceParser Parser = SendNodePerformanceParser();
    SendNodePerformanceSerializer Serializer = SendNodePerformanceSerializer();

    PCPerformance Performance = PCPerformance();
    Performance.CPUPerformance.Cores = 8;
    Performance.CPUPerformance.FrequencyHZ = 3600;
    Performance.CPUPerformance.CPULoad = 25;
    Performance.RAMPerformance.AvailablePhysicalBytes = 500;
    Performance.RAMPerformance.TotalPhysicalBytes = 1000;
    Performance.RAMPerformance.MemoryLoad = 50;

    SendNodePerformanceMessage* Msg = DBG_NEW SendNodePerformanceMessage(Performance);
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (SendNodePerformanceMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    Performance = Msg->GetNodePerformance();
    if  (
            Performance.CPUPerformance.Cores != 8 ||
            Performance.CPUPerformance.FrequencyHZ != 3600 ||
            Performance.CPUPerformance.CPULoad != 25 ||
            Performance.RAMPerformance.AvailablePhysicalBytes != 500 ||
            Performance.RAMPerformance.TotalPhysicalBytes != 1000 ||
            Performance.RAMPerformance.MemoryLoad != 50
        )
    {
        return -1;
    }
    return 0;
}
