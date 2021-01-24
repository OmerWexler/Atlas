#include <memory>

#include "Utils.h"
#include "BasicConnection.h"
#include "BasicServer.h"
#include "SimpleStringParser.h"
#include "SimpleStringSerializer.h"
#include "SimpleStringMessage.h"

#include "Logger.h"
#include "GridNode.h"

using namespace std;

int TestBasicCommunications() 
{
    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    BasicConnection Connection("Connection", true);
    BasicServer Server("Server", true);

    Connection.AddParser(shared_ptr<IParser>((IParser*) DBG_NEW SimpleStringParser()));
    Connection.AddSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SimpleStringSerializer()));

    Server.AddParser(shared_ptr<IParser>((IParser*) DBG_NEW SimpleStringParser()));
    Server.AddSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SimpleStringSerializer()));

    Server.Bind("127.0.0.1", "17000");
    Server.Listen(1);
    Connection.Connect("127.0.0.1", "17000");

    BasicConnection ServerConnection;
    Server.AcceptConnection("ServerConnection", ServerConnection);

    unique_ptr<IMessage> Msg((IMessage*) DBG_NEW SimpleStringMessage("Hello"));
    Connection.Send(Msg);
    ServerConnection.Recv(Msg);

    ServerConnection.Send(Msg);
    Connection.Recv(Msg);

    Connection.Disconnect();
    ServerConnection.Disconnect();

    return 0;
}