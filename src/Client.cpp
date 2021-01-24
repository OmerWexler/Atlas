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
#include "SimpleStringMessage.h"
#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main(int argc, char** argv) {
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    
    {
        Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);

        cout << "Client" << endl;
        Singleton<GridNode>::GetInstance().SetName("Client");

        int Result = -1;
        while (Result != 0)
        {
            Result = Singleton<GridNode>::GetInstance().ConnectToNode("127.0.0.1", "64000", true);
            Utils::CPSleep(1);
        }

        Singleton<GridNode>::GetInstance().GetAdmin().AddSerializer(shared_ptr<ISerializer>((ISerializer*) DBG_NEW SimpleStringSerializer()));
        Result = 1;
        while (true)
        {
            Result = Singleton<GridNode>::GetInstance().GetAdmin().SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SimpleStringMessage("AAAAA")));
            if (Result < 0)
            {
                break;
            }
            Utils::CPSleep(1);
        }

        system("pause");
    }

    if (_CrtDumpMemoryLeaks()) 
    {
        exit(-1);
    }
    else 
    {
        exit(0);
    }
}