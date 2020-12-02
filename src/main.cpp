#include "BasicConnection.h"
#include "SimpleStringParser.h"
#include "SimpleStringSerializer.h"
#include "SimpleStringMessage.h"

#include "Logger.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main() {
    {
        Logger.SetLogLevel(L_DEBUG);
        BasicConnection Connection("Connection");

        Connection.AddParser((IParser*) &SimpleStringParser());
        Connection.AddSerializer((ISerializer*) &SimpleStringSerializer());

        Connection.Connect("127.0.0.1", "17000");

        IMessage* Msg = Connection.Recv();
        Connection.Send(Msg);
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