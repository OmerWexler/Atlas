#include "BasicConnectionAndServer.cpp"
#include "WinSocketTest.cpp"
#include "TestSeperatorBasedMessages.cpp"
#include "TestSendJobPolicyMessages.cpp"
#include "TestCancelJobMessage.cpp"
#include "TestRequestBestNodeMessages.cpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

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

        default:
            break;
        }
    }
    else 
    {
        ExitCode += TestWinSocketCommunications();
        CheckMemory();

        ExitCode += TestBasicCommunications();
        CheckMemory();
    
        ExitCode += TestSeperatorBasedMessages();
        CheckMemory();
        
        ExitCode += TestSendJobPolicyMessages();
        CheckMemory();
        
        ExitCode += TestCancelJobMessage();
        CheckMemory();
        
        ExitCode += TestRequestBestNodeMessages();
        CheckMemory();
    }
    exit(CheckMemory() + ExitCode);
}