#include "SmartSubprocess.h"
#include "Utils.h"

#include <windows.h>

using namespace std;

int JobSubprocessTest() 
{
    // HANDLE                               hJob;
    // JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
    // PROCESS_INFORMATION                  pi   = { 0 };
    // STARTUPINFO                          si   = { 0 };


    // /*
    //  * Create a job object.
    //  */
    // hJob = CreateJobObject(NULL, NULL);

    // /*
    //  * Causes all processes associated with the job to terminate when the
    //  * last handle to the job is closed.
    //  */
    // jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    // SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));

    // /*
    //  * Create the process suspended.
    //  */
    // si.cb = sizeof(si);
    // CreateProcess(TEXT("C:\\Windows\\System32\\Notepad.exe"), NULL, NULL, NULL, FALSE, 
    //               CREATE_SUSPENDED | CREATE_BREAKAWAY_FROM_JOB /*Important*/, NULL, NULL, &si, &pi);

    // /*
    //  * Add the process to our job object.
    //  */
    // AssignProcessToJobObject(hJob, pi.hProcess); // Does not work if without CREATE_BREAKAWAY_FROM_JOB


    // /*
    //  * Start our suspended process.
    //  */
    // ResumeThread(pi.hThread);

    // /*
    //  * At this point, if we are closed, windows will automatically clean up
    //  * by closing any handles we have open. When the handle to the job object
    //  * is closed, any processes belonging to the job will be terminated.
    //  * Note: Grandchild processes automatically become part of the job and
    //  * will also be terminated. This behaviour can be avoided by using the
    //  * JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK limit flag.
    //  */

    // /*
    //  * Do what you like here. For demonstration purposes we will just wait
    //  * for the child process to complete. Click our close button to see
    //  * everything in action.
    //  */
    // WaitForSingleObject(pi.hProcess, 3000);
    // /*
    //  * Cleanup. As mentioned, Windows does this automagically when our process
    //  * exits, but it is good style to do it explicitly. 
    //  */
    // CloseHandle(pi.hThread);
    // CloseHandle(pi.hProcess);

    // CloseHandle(hJob);

    // return 0;

    // SmartSubprocess SP = SmartSubprocess("TestRun", "C:\\Windows\\System32\\Notepad.exe", "");

    // int Result = SP.Run();

    // SP.Kill();
    
    return 0;
}