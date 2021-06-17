#pragma once

#include <Windows.h>
#include "SmartSubprocess.h"

#define StrToLPSTR(Str) const_cast<char *>(Str.c_str())
#define NoEmptyStrToLPSTR(Str) Str == "" ? NULL : const_cast<char*>(Str.c_str())

const float SmartSubprocess::PollRate = 0.1f;
const int SmartSubprocess::BUFSIZE = 4096;

SmartSubprocess::SmartSubprocess(string Name, string Executeable, string CMDInput)
{
    Create(Name, Executeable, CMDInput);
}

void SmartSubprocess::Create(string Name, string Executeable, string CMDInput)
{
    this->Name = Name;
    this->Executeable = Executeable;
    this->CMDInput = CMDInput;
    Environment = "";
    WorkingDirectory = "";

    m_IsAlive = false;
    m_IsDone = false;

    JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };
    hJob = CreateJobObject(NULL, NULL);

    /*
     * Causes all processes associated with the job to terminate when the
     * last handle to the job is closed.
     */
    jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));
}

int SmartSubprocess::RedirectOutput(string OutFileName)
{
    OutFile.Create(OutFileName, "w", true);

    if (OutFile.IsOpen())
        return 0;
    else
        return -1;
}

void SmartSubprocess::SetWorkingDirectory(string Directory)
{
    this->WorkingDirectory = Directory;
}
    
int SmartSubprocess::Run()
{   
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
    saAttr.bInheritHandle = TRUE; 
    saAttr.lpSecurityDescriptor = NULL; 
    
    BOOL Result = CreatePipe(&OutStreamRead, &OutStreamWrite, &saAttr, 0);
    if (!Result)
        return GetLastError();
    
    Result = SetHandleInformation(OutStreamRead, HANDLE_FLAG_INHERIT, 0);
    if (!Result)
        return GetLastError();
    
    Result = CreatePipe(&InStreamRead, &InStreamWrite, &saAttr, 0);
    if (!Result)
        return GetLastError();
    
    Result = SetHandleInformation(InStreamWrite, HANDLE_FLAG_INHERIT, 0);
    if (!Result)
        return GetLastError();

    ZeroMemory( &si, sizeof(STARTUPINFO) );
    si.cb = sizeof(STARTUPINFO); 
    si.hStdError = OutStreamWrite;
    si.hStdOutput = OutStreamWrite;
    si.hStdInput = InStreamRead;
    si.dwFlags |= STARTF_USESTDHANDLES;

    Result = CreateProcessA(
        StrToLPSTR(Executeable),                        // LPCSTR lpApplicationName,
        StrToLPSTR(CMDInput),                           // LPSTR lpCommandLine,
        NULL,                                           // LPSECURITY_ATTRIBUTES lpProcessAttributes,
        NULL,                                           // LPSECURITY_ATTRIBUTES lpThreadAttributes,
        TRUE,                                           // BOOL bInheritHandles,
            CREATE_SUSPENDED |                          // DWORD dwCreationFlags,
            CREATE_BREAKAWAY_FROM_JOB,                  // DWORD dwCreationFlags,
        NULL,                                           // LPVOID lpEnvironment,
        NoEmptyStrToLPSTR(WorkingDirectory),            // LPCSTR lpCurrentDirectory,
        (LPSTARTUPINFOA)&si,                                            // LPSTARTUPINFOA lpStartupInfo,
        &pi);                                           // LPPROCESS_INFORMATION lpProcessInformation
    
    if (!Result)
        return GetLastError();
    
    CloseHandle(OutStreamWrite);
    CloseHandle(InStreamRead);

    /*
     * Add the process to our job object.
     */
    AssignProcessToJobObject(hJob, pi.hProcess); // Does not work if without CREATE_BREAKAWAY_FROM_JOB

    /*
     * Start our suspended process.
     */
    ResumeThread(pi.hThread);

    m_IsAlive = true;

    Periodic = SmartThread(
        "Periodic SP - " + Name, 
        PollRate, 
        &SmartSubprocess::PeriodicFunc,
        this
    );
    
    return 0;
}

void SmartSubprocess::PeriodicFunc()
{
    DWORD lpExitCode = STILL_ACTIVE;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pi.dwProcessId);
    
    GetExitCodeProcess(hProcess, &lpExitCode);
    if (lpExitCode != STILL_ACTIVE)
    {
        m_IsDone = true;
        m_IsAlive = false;
    }

    DWORD dwRead; 

    CHAR chBuf[BUFSIZE];
    BOOL Result = ReadFile( OutStreamRead, chBuf, BUFSIZE, &dwRead, NULL);

    if (Result && dwRead > 0)
    {
        string Read = string(chBuf).substr(0, dwRead);

        OutStream += Read;
        
        if (OutFile.IsOpen())
            OutFile.Write(Read, dwRead);
    }
}

int SmartSubprocess::Kill()
{
    DWORD lpExitCode = 0;
    TerminateProcess(pi.hProcess, lpExitCode);
        
    /*
     * Cleanup. As mentioned, Windows does this automagically when our process
     * exits, but it is good style to do it explicitly. 
     */
    try { CloseHandle(pi.hThread); } catch(...) {}
    try { CloseHandle(pi.hProcess); } catch(...) {}
    try { CloseHandle(OutStreamRead); } catch(...) {}
    try { CloseHandle(InStreamWrite); } catch(...) {}
    try { CloseHandle(hJob); } catch(...) {}

    if (Periodic.GetIsRunning())
        Periodic.Stop();

    if (OutFile.IsOpen())
        OutFile.Close();
    
    return lpExitCode;
}

string SmartSubprocess::GetOutput()
{
    return OutStream;
}