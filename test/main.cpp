#include "BasicConnectionAndServer.cpp"
#include "WinSocketTest.cpp"
#include "TestSeperatorBasedMessages.cpp"
#include "TestSendJobPolicyMessages.cpp"
#include "TestCancelJobMessage.cpp"
#include "TestSendNodePerformanceMessages.cpp"
#include "WinPerformanceAnalyzerTest.cpp"
#include "TestSendJobMessage.cpp"
#include "TestSendJobOutputMessage.cpp"
#include "TestEncryptionModule.cpp"
#include "Logger.h"
#include "Utils.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(int argc, char** argv)
{   
    Utils::SetupMemoryCheck();
    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().SetLogFileName("", "Tests.txt");

    int ExitCode = 0;
    
    if (argc > 1)
    {
        int TestID = atoi(argv[1]);
        switch (TestID)
        {
        case 0:
            // ExitCode = TestWinSocketCommunications();
            break;

        case 1:
            // ExitCode = TestBasicCommunications();
            break;
        
        case 2:
            // ExitCode = TestSeperatorBasedMessages();
            break;

        case 3:
            // ExitCode = TestSendJobPolicyMessages();
            break;

        case 4:
            // ExitCode = TestCancelJobMessage();
            break;

        case 5:
            // ExitCode = TestSendNodePerformanceMessages();
            break;

        case 6:
            // ExitCode = TestSendJobMessage();
            break;

        case 7:
            // ExitCode = TestSendJobOutputMessage();
            break;

        case 8:
            // ExitCode = WinPerformanceAnalyzerTest();
            break;

        case 9:
            ExitCode = TestEncryptionModule();
            break;

        default:
            break;
        }
    }
    else 
    {

        // Singleton<Logger>::GetInstance().Info("Starting TestWinSocketCommunications...");
        // ExitCode = TestWinSocketCommunications();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");

        // Singleton<Logger>::GetInstance().Info("Starting TestBasicCommunications...");
        // ExitCode = TestBasicCommunications();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
    
        // Singleton<Logger>::GetInstance().Info("Starting TestSeperatorBasedMessages...");
        // ExitCode = TestSeperatorBasedMessages();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting TestSendJobPolicyMessages...");
        // ExitCode = TestSendJobPolicyMessages();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting TestCancelJobMessage...");
        // ExitCode = TestCancelJobMessage();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting TestSendNodePerformanceMessages...");
        // ExitCode = TestSendNodePerformanceMessages();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting TestSendJobMessage...");
        // ExitCode = TestSendJobMessage();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting TestSendJobOutputMessage...");
        // ExitCode = TestSendJobOutputMessage();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        // Singleton<Logger>::GetInstance().Info("Starting WinPerformanceAnalyzerTest...");
        // ExitCode = WinPerformanceAnalyzerTest();
        // if (ExitCode != 0)
        //     return ExitCode;
        // printf("\n");
        
        Singleton<Logger>::GetInstance().Info("Starting TestEncryptionModule...");
        ExitCode = TestEncryptionModule();
        if (ExitCode != 0)
            return ExitCode;
        printf("\n");
    }
    return ExitCode;
}