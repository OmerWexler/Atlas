#pragma once

using namespace std;

#include <string>
#include <fstream>

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

    Logger() {}
    
    string FormatMessage(string Msg); 
    string GetTime();
    void Log(string Msg, LogLevel Level);
public:
    Logger(Logger &other) = delete;
    void operator=(const Logger &) = delete;

    void SetLogFileName(string Path, string Name);
    void SetLogFileName(string Name);
    void SetLogLevel(LogLevel Level);

    void Debug(string Msg);
    void Info(string Msg);
    void Error(string Msg);
    void Warning(string Msg);

    inline static Logger& GetInstance() 
    {
        static Logger Instance;
        return Instance;
    }

    int Clean();
    ~Logger();
};