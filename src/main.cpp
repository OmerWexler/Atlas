#include "Logger.h"
#include "SmartThread.h"
// #include "JobLog.h"
// #include "GridNode.h"
// #include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

void TestFunc(int f)
{
    static int i;
    i = i + f;
    Singleton<Logger>::GetInstance().Debug(to_string(i + f));
}

int main(int argc, char** argv) {
    Utils::SetupMemoryCheck();

    {
        Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
        SmartThread L("TestThread", 1.f, TestFunc, 1);
        Utils::CPSleep(5);
        L.Stop();
    }
}