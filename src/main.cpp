#include "Logger.h"
#include "JobLog.h"
#include "GridNode.h"
#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main(int argc, char** argv) {
    Utils::SetupMemoryCheck();

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