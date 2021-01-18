#include <memory>
#include <string>
#include <iostream>

#include "NodeContainer.h"
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
    {
        SingletonLogger::GetInstance().SetLogLevel(L_DEBUG);

        cout << "Client" << endl;
        SingletonNodeGrid::GetInstance().SetName("Client");

        int Result = -1;
        while (Result != 0)
        {
            Result = SingletonNodeGrid::GetInstance().ConnectToNode("127.0.0.1", "64000", true);
            Utils::CPSleep(1);
        }

        SingletonNodeGrid::GetInstance().GetAdmin().AddSerializer(shared_ptr<ISerializer>((ISerializer*) new SimpleStringSerializer()));
        Result = 1;
        while (true)
        {
            Result = SingletonNodeGrid::GetInstance().GetAdmin().SendMessage(unique_ptr<IMessage>((IMessage*) new SimpleStringMessage("AAAAA")));
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