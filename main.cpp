#include <iostream>

#include "WinServerSocket.h"
#include "WinConnectionSocket.h"
#include "Logger.h"

using namespace std;

int main(int, char**) {

    Logger::GetInstance()->SetLogLevel(LogLevel::L_DEBUG);
    Logger::GetInstance()->SetLogFileName("AtlasLog.txt");
    Logger::GetInstance()->Info("HelloWorld");

    WinServerSocket Server = WinServerSocket("Server");
    WinConnectionSocket Connection = WinConnectionSocket("Conenction");

    Connection.Connect("127.0.0.1", "17000");

    Connection.Send("Hello");

    string Msg;
    Connection.Recv(Msg, 5);
}