#pragma once

#include "SmartThread.h"
#include "File.h"
#include <windows.h>

using namespace std;

class SmartSubprocess
{
private:
    static const int BUFSIZE; 

    string Name;
    string Executeable;
    string CMDInput;
    string Environment;
    string WorkingDirectory;

    HANDLE hJob;
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { 0 };

    SECURITY_ATTRIBUTES saAttr;
    HANDLE InStreamRead = NULL;
    HANDLE InStreamWrite = NULL;
    HANDLE OutStreamRead = NULL;
    HANDLE OutStreamWrite = NULL;

    bool m_IsAlive;
    bool m_IsDone;

    SmartThread Periodic;
    static const float PollRate;

    File OutFile;
    string OutStream;

    void PeriodicFunc();

public:
    SmartSubprocess() {};
    SmartSubprocess(string Name, string Module, string CMDInput);
    
    void Create(string Name, string Module, string CMDInput);
    
    int RedirectOutput(string OutFileName);
    
    void SetWorkingDirectory(string Directory);

    int Run();
    
    void Kill();
    bool IsAlive() { return m_IsAlive; }
    bool IsDone() { return m_IsDone; }
    
    string GetOutput();

    ~SmartSubprocess() 
    { 
        Kill();
        OutFile.Close(); 
    }
};