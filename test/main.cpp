#include "BasicConnectionAndServer.cpp"
#include "WinSocketTest.cpp"
#include "TestSeperatorBasedMessages.cpp"
#include "TestSendJobPolicyMessages.cpp"
#include "TestCancelJobMessage.cpp"
#include "TestRequestBestNodeMessages.cpp"
#include "TestSendJobMessage.cpp"
#include "TestSendJobOutputMessage.cpp"
#include "Logger.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int CheckMemory()
{
    if (_CrtDumpMemoryLeaks()) 
    {
        return -2;
    }
    else 
    {
        return 0;
    }
}

int main(int argc, char** argv)
{   
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

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
        ExitCode += TestWinSocketCommunications();
        CheckMemory();
        printf("\n");

        Singleton<Logger>::GetInstance().Info("Starting TestBasicCommunications...");
        ExitCode += TestBasicCommunications();
        CheckMemory();
        printf("\n");
    
        Singleton<Logger>::GetInstance().Info("Starting TestSeperatorBasedMessages...");
        ExitCode += TestSeperatorBasedMessages();
        CheckMemory();
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobPolicyMessages...");
        ExitCode += TestSendJobPolicyMessages();
        CheckMemory();
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestCancelJobMessage...");
        ExitCode += TestCancelJobMessage();
        CheckMemory();
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestRequestBestNodeMessages...");
        ExitCode += TestRequestBestNodeMessages();
        CheckMemory();
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobMessage...");
        ExitCode += TestSendJobMessage();
        CheckMemory();
        printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestSendJobOutputMessage...");
        ExitCode += TestSendJobOutputMessage();
        CheckMemory();
        printf("\n");
    }
    exit(CheckMemory() + ExitCode);
}