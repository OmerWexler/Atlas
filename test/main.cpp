#include "BasicConnectionAndServer.cpp"
#include "WinSocketTest.cpp"
#include "TestSeperatorBasedMessages.cpp"
#include "TestSendJobPolicyMessages.cpp"
#include "TestCancelJobMessage.cpp"
#include "TestRequestBestNodeMessages.cpp"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

int main(int argc, char **argv)
{
    int TestID = atoi(argv[1]);
    switch (TestID)
    {
    case 0:
        exit(TestWinSocketCommunications());
        break;

    case 1:
        exit(TestBasicCommunications());
        break;
    
    case 2:
        exit(TestSeperatorBasedMessages());
        break;

    case 3:
        exit(TestSendJobPolicyMessages());
        break;

    case 4:
        exit(TestCancelJobMessage());
        break;

    case 5:
        exit(TestRequestBestNodeMessages());
        break;

    default:
        break;
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