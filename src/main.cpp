#include <memory>
#include <string>
#include <iostream>

#include "Logger.h"
#include "NodeContainer.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"
#include "SimpleStringSerializer.h"
#include "SimpleStringParser.h"
#include "SimpleStringMessage.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main(int argc, char** argv) {
    {
        SingletonLogger::GetInstance().SetLogLevel(L_DEBUG);
        BasicConnection Connection("Connection");
        BasicServer Server("Server");

        Connection.AddParser(shared_ptr<IParser>((IParser*) new SimpleStringParser()));
        Connection.AddSerializer(shared_ptr<ISerializer>((ISerializer*) new SimpleStringSerializer()));

        Server.AddParser(shared_ptr<IParser>((IParser*) new SimpleStringParser()));
        Server.AddSerializer(shared_ptr<ISerializer>((ISerializer*) new SimpleStringSerializer()));

        Server.Bind("127.0.0.1", "17000");
        Server.Listen(1);
        Connection.Connect("127.0.0.1", "17000");

        BasicConnection ServerConnection;
        Server.AcceptConnection("ServerConnection", ServerConnection);
        

        unique_ptr<IMessage> Msg((IMessage*) new SimpleStringMessage("Hello"));
        // Connection.Send(Msg);
        Connection.Disconnect();
        ServerConnection.Recv(Msg);

        // ServerConnection.Send(Msg);
        // Connection.Recv(Msg);

        // Connection.Disconnect();
        // ServerConnection.Disconnect();

        return 0;
    }

    system("pause");
    if (_CrtDumpMemoryLeaks()) 
    {
        exit(-1);
    }
    else 
    {
        exit(0);
    }
}