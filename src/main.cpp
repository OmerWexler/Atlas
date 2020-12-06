#include <memory>

#include "BasicConnection.h"
#include "BasicServer.h"
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
        BasicServer Server("Server");

        Connection.AddParser((IParser*) new SimpleStringParser());
        Connection.AddSerializer((ISerializer*) new SimpleStringSerializer());

        Server.AddParser((IParser*) new SimpleStringParser());
        Server.AddSerializer((ISerializer*) new SimpleStringSerializer());

        Server.Bind("127.0.0.1", "17000");
        Server.Listen(1);
        Connection.Connect("127.0.0.1", "17000");

        BasicConnection ServerConnection;
        Server.AcceptConnection("ServerConnection", ServerConnection);

        unique_ptr<IMessage> Msg((IMessage*) new SimpleStringMessage("Hello"));
        Connection.Send(Msg);
        ServerConnection.Recv(Msg);

        ServerConnection.Send(Msg);
        Connection.Recv(Msg);

        Connection.Disconnect();
        ServerConnection.Disconnect();
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