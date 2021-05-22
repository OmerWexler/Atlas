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
    BasicConnection Connection("Connection", false);
    BasicServer Server("Server", false);

    Connection.AddParser(ATLS_CREATE_SHARED_PRSR(SimpleStringParser));
    Connection.AddSerializer(ATLS_CREATE_SHARED_SRLZR(SimpleStringSerializer));

    Server.AddParser(ATLS_CREATE_SHARED_PRSR(SimpleStringParser));
    Server.AddSerializer(ATLS_CREATE_SHARED_SRLZR(SimpleStringSerializer));

    Server.Bind("127.0.0.1", "17002");
    Server.Listen(1);
    Connection.Connect("127.0.0.1", "17002");

    BasicConnection ServerConnection;
    Server.AcceptConnection("ServerConnection", ServerConnection);

    unique_ptr<IMessage> Msg;
    
    Connection.Recv(Msg);
    ServerConnection.Recv(Msg);

    Msg.reset((IMessage*) DBG_NEW SimpleStringMessage("Hello"));
    Connection.Send(Msg);
    ServerConnection.Recv(Msg);

    ServerConnection.Send(Msg);
    Connection.Recv(Msg);

    Connection.RegenerateKey();
    ServerConnection.RegenerateKey();

    Connection.Recv(Msg);
    ServerConnection.Recv(Msg);

    Msg.reset((IMessage*) DBG_NEW SimpleStringMessage("Hello"));
    Connection.Send(Msg);
    ServerConnection.Recv(Msg);

    ServerConnection.Send(Msg);
    Connection.Recv(Msg);

    Connection.Disconnect();
    ServerConnection.Disconnect();

    return 0;
}