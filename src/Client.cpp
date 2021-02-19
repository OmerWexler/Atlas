#include <memory>
#include <string>
#include <iostream>

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "SimpleStringSerializer.h"
#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"
#include "SendJobMessage.h"
#include "JobLog.h"
#include "Argument.h"
#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main(int argc, char** argv) {
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    
    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().SetLogFileName("E:\\Desktop\\2021 Cyber Project\\Atlas\\build\\src\\Debug", "Client.txt");

    cout << "Client" << endl;
    Singleton<GridNode>::GetInstance().SetName("Client");

    int Result = -1;
    while (Result != 0)
    {
        Result = Singleton<GridNode>::GetInstance().ConnectToNode("127.0.0.1", "64000", true);
        Utils::CPSleep(1);
    }

    string Port = "64001";
    Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", "64001");
    while (Result != 0)
    {
        Port = to_string(atoi(Port.c_str()) + 1);
        Utils::CPSleep(1);
        Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", Port);
    }

    Singleton<GridNode>::GetInstance().GetAdmin().AddSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SimpleStringSerializer()));
    while (true)
    {
        // Result = Singleton<GridNode>::GetInstance().GetAdmin().SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SimpleStringMessage("AAAAA")));
        Result = Singleton<GridNode>::GetInstance().GetAdmin().SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SendJobMessage(
            shared_ptr<IJob>((IJob*) DBG_NEW JobLog()),
            vector<Argument>{Argument("TESTING TESTING", false), Argument("TESTING22 TESTING22", false)},
            "/Server/Client"
        )));

        if (Result < 0)
        {
            break;
        }
        Utils::CPSleep(2);
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