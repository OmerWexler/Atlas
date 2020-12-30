#include "BasicConnection.h"
#include "BasicServer.h"
#include "SimpleStringParser.h"
#include "SimpleStringSerializer.h"
#include "SimpleStringMessage.h"

#include "Logger.h"

using namespace std;

int TestBasicCommunications() 
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

    return 0;
}