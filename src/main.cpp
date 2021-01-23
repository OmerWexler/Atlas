#include "Logger.h"
#include "JobLog.h"
#include "GridNode.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main(int argc, char** argv) {
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

    {
        Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
        Singleton<GridNode>::GetInstance().SetName("AAAA");
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