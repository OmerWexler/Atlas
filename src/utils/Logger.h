#pragma once

using namespace std;

#include <string>
#include <fstream>

#include "Singleton.h"

enum LogLevel {
    L_DEBUG = 4,
    L_INFO = 3,
    L_WARNING = 2,
    L_ERROR = 1
};

class Logger
{
private:
    ofstream LogFile;
    LogLevel Level = L_ERROR;

    string FormatMessage(string Msg); 
    string GetTime();
    void Log(string Msg, LogLevel Level);

public:
    Logger() {};

    void SetLogFileName(string Path, string Name);
    void SetLogLevel(LogLevel Level);
    
    void Debug(string Msg);
    void Info(string Msg);
    void Error(string Msg);
    void Warning(string Msg);

    ~Logger();
};