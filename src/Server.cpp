#include <memory>
#include <string>
#include <iostream>

#include "NodeContainer.h"
#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"
#include "TestHandler.h"

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"
#include "SimpleStringMessage.h"
#include "SimpleStringParser.h"

#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")


using namespace std;

int main() {
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

    {

        GridNode* Node = new GridNode();

        SingletonLogger::GetInstance().SetLogLevel(L_DEBUG);

        SingletonNodeGrid::GetInstance().SetName("Server");
        SingletonNodeGrid::GetInstance().AddCollectiveParser(shared_ptr<IParser>((IParser*) new SimpleStringParser()));
        SingletonNodeGrid::GetInstance().AddHandler(unique_ptr<IHandler>((IHandler*) new TestHandler()));

        int Result;
        Result = SingletonNodeGrid::GetInstance().Setup("127.0.0.1", "64000");
        if (Result != 0)
            exit(Result);

        while(true)
        {
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