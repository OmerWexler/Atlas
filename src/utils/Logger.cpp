#pragma once

#include "Logger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

#ifdef DEBUG
    string Logger::GetTime()
    {
        time_t Now = time(0);
        tm *LocalTime = &tm();
        localtime_s(LocalTime, &Now);

        string Hour = to_string(LocalTime->tm_hour);
        if (Hour.size() == 1)
            Hour = "0" + Hour;

        string Minute = to_string(LocalTime->tm_min);
        if (Minute.size() == 1)
            Minute = "0" + Minute;

        string Second = to_string(LocalTime->tm_sec);
        if (Second.size() == 1)
            Second = "0" + Second;

        return  Hour + "_" + Minute + "_" + Second;
    }

    void Logger::SetLogFileName(string Path, string Name)
    {   
        string FullName;
        if (Path != "") 
        {
            FullName = Path + "\\" + GetTime() + "_" + Name;
        } 
        else 
        {
            FullName = GetTime() + "_" + Name;
        }

        LogFile.open(FullName, ios::out);
        LogFile = ofstream(FullName);

        if (!LogFile) 
        {
            this->Warning("Couldn't create logfile - " + FullName);
        } 
        else 
        {
            this->Info("Created logfile - " + FullName);
        }
    }

    void Logger::Log(string Msg, LogLevel Level) 
    {
        string FullMsg = this->FormatMessage(Msg);

        if (this->Level >= Level) 
        {
            cout << FullMsg;
        }

        LogFile << FullMsg;
    }

    void Logger::SetLogLevel(LogLevel Level) 
    {
        this->Level = Level; 
    }

    string Logger::FormatMessage(string Msg) 
    {
        return GetTime() + ", " + Msg + "\n";
    }

    void Logger::Debug(string Msg) 
    {
        Log("DEBUG, " + Msg, LogLevel::L_DEBUG);
    }

    void Logger::Info(string Msg) 
    {
        Log("INFO, " + Msg, LogLevel::L_INFO);
    }

    void Logger::Error(string Msg) 
    {
        Log("ERROR, " + Msg, LogLevel::L_ERROR);
    }

    void Logger::Warning(string Msg) 
    {
        Log("WARNING, " + Msg, LogLevel::L_WARNING);
    }

    Logger::~Logger()
    {
        if (LogFile) 
        {
            LogFile.close();
        }
    }
#else
    string Logger::GetTime()
    {
        return  "";
    }

    void Logger::SetLogFileName(string Path, string Name)
    {   
    }

    void Logger::Log(string Msg, LogLevel Level) 
    {
    }

    void Logger::SetLogLevel(LogLevel Level) 
    {
    }

    string Logger::FormatMessage(string Msg) 
    {
        return "";
    }

    void Logger::Debug(string Msg) 
    {
    }

    void Logger::Info(string Msg) 
    {
    }

    void Logger::Error(string Msg) 
    {
    }

    void Logger::Warning(string Msg) 
    {
    }

    Logger::~Logger()
    {
    }
#endif
