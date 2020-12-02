#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int TestWinSocketCommunicationSequence() {
    {
        Logger::GetInstance().SetLogLevel(LogLevel::L_ERROR);
        Logger::GetInstance().SetLogFileName("Debug", "WinSocketCommsSequence.txt");

        WinConnectionSocket Connection = WinConnectionSocket("Connection");
        WinServerSocket Server = WinServerSocket("Server");

        Server.Bind("127.0.0.1", "17000");
        Server.Listen();

        Connection.Connect("127.0.0.1", "17000");
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
            Logger::GetInstance().Error("Received unexpected message");
            return -1;
        }

        Connection.Disconnect();
        ServerClient->Disconnect();
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