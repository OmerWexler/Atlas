#include <iostream>

#include "WinServerSocket.h"
#include "WinConnectionSocket.h"
#include "Logger.h"

using namespace std;

int main(int, char**) {

    Logger::GetInstance()->SetLogLevel(LogLevel::L_ERROR);
    Logger::GetInstance()->SetLogFileName("AtlasLog.txt");
    Logger::GetInstance()->Info("HelloWorld");
}
