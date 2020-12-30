#include <memory>
#include <string>

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main() {
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

    if (_CrtDumpMemoryLeaks()) 
    {
        Logger::GetInstance().Error("Run done - memory leak detected!");
        return -1;
    }
    else 
    {
        Logger::GetInstance().Info("Run done - memory clean!");
        return 0;
    }
}