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

int StartServer(string Host, string Port, string Name)
{
    GridNode Node;
    cout << "Server" << endl;
    Node = GridNode(Name);
    
    int Result;
    Result = Node.Setup(Host, Port);
    if (Result != 0)
        return Result;

    while(Node.ConnectionListener.joinable())
    {
    }
    return 0;
}

int StartClient(string Host, string Port, string Name)
{
    cout << "Client" << endl;

    NodeCotainer::Node = GridNode(Name);
    NodeCotainer::Node.ConnectToNode(Host, Port, true);
    return 0;
}

int main(int argc, char** argv) {
    {
        Logger::GetInstance().SetLogLevel(L_DEBUG);

        if (argc > 0)
        {
            if (string(argv[1]) == "server")
            {
                exit(StartServer(argv[2], argv[3], argv[4]));
            }
            else if (string(argv[1]) == "client")
            {
                exit(StartClient(argv[2], argv[3], argv[4]));
            }
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