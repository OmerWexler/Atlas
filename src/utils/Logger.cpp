#pragma once

#include "Logger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

// Logger* Logger::Instance = nullptr;

string Logger::GetTime()
{
    time_t Now = time(0);
    tm *LocalTime = &tm();
    localtime_s(LocalTime, &Now);

    return to_string(LocalTime->tm_hour) + ":" + to_string(LocalTime->tm_min) + ":" + to_string(LocalTime->tm_sec);
}

void Logger::SetLogFileName(string Name)
{
    SetLogFileName("", Name);
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