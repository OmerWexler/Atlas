#include <memory>

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
        Logger::GetInstance().SetLogLevel(L_DEBUG);
        BasicConnection Connection("Connection");

        Connection.AddParser((IParser*) new SimpleStringParser());
        Connection.AddSerializer((ISerializer*) new SimpleStringSerializer());

        Connection.Connect("127.0.0.1", "17000");

        unique_ptr<IMessage> Msg;
        Connection.Recv(Msg);
        Connection.Send(Msg);

        Connection.Disconnect();
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