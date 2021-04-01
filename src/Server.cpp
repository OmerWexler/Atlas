#include <memory>
#include <string>
#include <iostream>

#include "Utils.h"

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "TestCore.h"

#include "SimpleStringParser.h"

#include "JobLog.h"

using namespace std;

int main() {
    Utils::SetupMemoryCheck();
    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().SetLogFileName("E:\\Desktop\\2021 Cyber Project\\Atlas\\build\\src\\Debug", "Server.txt");
    
    Singleton<GridNode>::GetInstance().SetName("Server");
    Singleton<GridNode>::GetInstance().AddCollectiveParser(ATLS_CREATE_SHARED_PRSR(SimpleStringParser)));

    int Result;
    Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", "22000");
    if (Result != 0)
    {
        Singleton<GridNode>::GetInstance().StopPeriodics();
        exit(Result);
    }

    system("pause");
    Singleton<GridNode>::GetInstance().StopPeriodics();
    system("pause");
    return 0;
}