#include <memory>
#include <string>
#include <iostream>

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"
#include "TestHandler.h"

#include "SimpleStringParser.h"

#include "Utils.h"
#include "JobLog.h"

using namespace std;

int main() {
    Utils::SetupMemoryCheck();

    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().Debug("HHH");
    Singleton<GridNode>::GetInstance().AddCollectiveParser(shared_ptr<IParser>((IParser*) new SimpleStringParser()));
    Singleton<GridNode>::GetInstance().AddHandler(unique_ptr<IHandler>((IHandler*) new TestHandler()));

    int Result;
    Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", "64000");
    if (Result != 0)
    {
        Singleton<GridNode>::GetInstance().Stop();
        exit(Result);
    }

    Utils::CPSleep(5);
    while(Singleton<GridNode>::GetInstance().GetNumberOfConnections() > 0)
    {
        Utils::CPSleep(5);
    }

    Singleton<GridNode>::GetInstance().Stop();
    system("pause");
    exit(0);
}