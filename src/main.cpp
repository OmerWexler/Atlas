#include <memory>
#include <string>

#include "BasicConnection.h"
#include "BasicServer.h"
#include "SeperatorBasedSerializer.h"
#include "SeperatorBasedParser.h"
#include "SeperatorBasedMessage.h"

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main() {
    {
        Logger::GetInstance().SetLogLevel(L_DEBUG);

        SeperatorBasedParser Parser = SeperatorBasedParser();
        SeperatorBasedSerializer Serializer = SeperatorBasedSerializer();
        SeperatorBasedMessage* Msg = new SeperatorBasedMessage();
        Msg->AddValue("AAA");
        Msg->AddValue("BBBB");
        Msg->AddValue("CC");
        
        Logger::GetInstance().Info(
            Msg->GetValues()[0] + " " +
            Msg->GetValues()[1] + " " +
            Msg->GetValues()[2] + " "
        );
        
        string SMsg = Serializer.Serialize((IMessage*)Msg);
        Logger::GetInstance().Info(string(SMsg));

        if (Parser.CanParse(SMsg))
            Msg = (SeperatorBasedMessage*) Parser.Parse(SMsg);

        Logger::GetInstance().Info(
            Msg->GetValues()[0] + " " +
            Msg->GetValues()[1] + " " +
            Msg->GetValues()[2] + " "
        );
        delete Msg;
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