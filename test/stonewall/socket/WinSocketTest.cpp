#include "Utils.h"
#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"

using namespace std;

int TestWinSocketCommunications() 
{
    Singleton<Logger>::GetInstance().SetLogLevel(LogLevel::L_ERROR);
    Singleton<Logger>::GetInstance().SetLogFileName("Debug", "WinSocketCommsSequence.txt");

    WinConnectionSocket Connection = WinConnectionSocket("Connection", true);
    WinServerSocket Server = WinServerSocket("Server", true);

    Server.Bind("127.0.0.1", "18001");
    Server.Listen(1);

    Connection.Connect("127.0.0.1", "18001");
    unique_ptr<IConnectionSocket> ServerClient;
    Server.AcceptConnection("ServerClient", ServerClient);

    string Msg;
    Connection.Send("Hello");
    ServerClient->Recv(Msg, 5);

    if (Msg != "Hello")
    {   
        return -1;
    }
    
    ServerClient->Send(Msg);
    Connection.Recv(Msg, 5);
    if (Msg != "Hello")
    {   
        Singleton<Logger>::GetInstance().Error("Received unexpected message");
        return -1;
    }

    Connection.Disconnect();
    ServerClient->Disconnect();

    return 0;
}