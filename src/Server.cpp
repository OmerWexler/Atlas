#include <memory>
#include <string>
#include <iostream>

#include "NodeContainer.h"
#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"
#include "SimpleStringMessage.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")


GridNode NodeCotainer::Node = GridNode();

using namespace std;

int main() {
    {
        Logger::GetInstance().SetLogLevel(L_DEBUG);

        cout << "Server" << endl;
        NodeCotainer::Node = GridNode("Server");

        int Result;
        Result = NodeCotainer::Node.Setup("127.0.0.1", "64000");
        if (Result != 0)
            exit(Result);

        while(NodeCotainer::Node.ConnectionListener.joinable())
        {

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