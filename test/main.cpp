#include "BasicConnectionAndServer.cpp"
#include "WinSocketTest.cpp"
#include "TestSeperatorBasedMessages.cpp"
#include "TestSendJobPolicyMessages.cpp"
#include "TestCancelJobMessage.cpp"
#include "TestRequestBestNodeMessages.cpp"
#include "TestSendJobMessage.cpp"
#include "TestSendJobOutputMessage.cpp"
#include "Logger.h"
#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(int argc, char** argv)
{   
    Utils::SetupMemoryCheck();

    int ExitCode = 0;
    
    if (argc > 1)
    {
        int TestID = atoi(argv[1]);
        switch (TestID)
        {
        case 0:
            ExitCode = TestWinSocketCommunications();
            break;

        case 1:
            ExitCode = TestBasicCommunications();
            break;
        
        case 2:
            ExitCode = TestSeperatorBasedMessages();
            break;

        case 3:
            ExitCode = TestSendJobPolicyMessages();
            break;

        case 4:
            ExitCode = TestCancelJobMessage();
            break;

        case 5:
            ExitCode = TestRequestBestNodeMessages();
            break;

        case 6:
            ExitCode = TestSendJobMessage();
            break;

        case 7:
            ExitCode = TestSendJobOutputMessage();
            break;

        default:
            break;
        }
    }
    else 
    {
        Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);

        Singleton<Logger>::GetInstance().Info("Starting TestWinSocketCommunications...");
        ExitCode = TestWinSocketCommunications();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");

        Singleton<Logger>::GetInstance().Info("Starting TestBasicCommunications...");
        ExitCode = TestBasicCommunications();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
    
        Singleton<Logger>::GetInstance().Info("Starting TestSeperatorBasedMessages...");
        ExitCode = TestSeperatorBasedMessages();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobPolicyMessages...");
        ExitCode = TestSendJobPolicyMessages();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestCancelJobMessage...");
        ExitCode = TestCancelJobMessage();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestRequestBestNodeMessages...");
        ExitCode = TestRequestBestNodeMessages();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobMessage...");
        ExitCode = TestSendJobMessage();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobOutputMessage...");
        ExitCode = TestSendJobOutputMessage();
        if (ExitCode != 0)
            exit(ExitCode);
        printf("\n");
    }
    exit(ExitCode);
}