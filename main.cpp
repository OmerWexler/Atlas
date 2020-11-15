#include <iostream>

#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"

using namespace std;

int main(int, char**) {

    Logger::GetInstance()->SetLogLevel(LogLevel::L_DEBUG);
    Logger::GetInstance()->SetLogFileName("AtlasLog.txt");
    Logger::GetInstance()->Info("HelloWorld");

    WinConnectionSocket Connection = WinConnectionSocket("Connection");
    WinServerSocket Server = WinServerSocket("Server");

    Server.Bind("127.0.0.1", "17000");
    Server.Listen();

    Connection.Connect("127.0.0.1", "17000");
    IConnectionSocket* ServerClient = Server.AcceptConnection("ServerClient");

    string Msg;
    Connection.Send("Hello");
    ServerClient->Recv(Msg, 5);
    
    ServerClient->Send(Msg);
    Connection.Recv(Msg, 5);

    Connection.Disconnect();
    ServerClient->Disconnect();
}