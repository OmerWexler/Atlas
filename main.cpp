#include <iostream>

#include "WinConnectionSocket.h"
#include "WinServerSocket.h"
#include "Logger.h"
#include "IMessage.h"
#include "BasicConnection.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

class MessageTest: IMessage
{
private:
    string Value;

public:
    string GetType() const
    {
        return "Test";
    }

    MessageTest(string Value)
    {
        this->Value = Value;
    }

    string GetValue()
    {
        return Value;
    }
};

class ParserTest: IParser
{
    string GetType() const
    {
        return "Test";
    }

    IMessage* Parse(const string& SMsg)
    {
        return (IMessage*) new MessageTest(SMsg);
    }

    bool CanParse(const string& SMsg) const
    {
        return true;
    }
};

int main(int, char**) {
    {
        Logger::GetInstance().SetLogLevel(LogLevel::L_DEBUG);
        Logger::GetInstance().SetLogFileName("AtlasLog.txt");
        Logger::GetInstance().Info("HelloWorld");

        // WinConnectionSocket Connection = WinConnectionSocket("Connection");
        // WinServerSocket Server = WinServerSocket("Server");

        // Server.Bind("127.0.0.1", "17000");
        // Server.Listen();

        // Connection.Connect("127.0.0.1", "17000");
        // IConnectionSocket* ServerClient = Server.AcceptConnection("ServerClient");

        // string SMsg;
        // Connection.Send("Hello");
        // ServerClient->Recv(SMsg, 5);
        
        // ServerClient->Send(SMsg);
        // Connection.Recv(SMsg, 5);

        // Connection.Disconnect();
        // ServerClient->Disconnect();
        
        // delete (WinConnectionSocket*) ServerClient;
    
        BasicConnection Connection("Connection");
        Connection.AddParser((IParser*) new ParserTest());

        Connection.Connect("127.0.0.1", "17000");

        MessageTest* Message = (MessageTest*) Connection.Recv();
        cout << Message->GetValue();

        delete Message;
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