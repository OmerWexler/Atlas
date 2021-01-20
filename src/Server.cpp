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
    // while ()
    // Utils::CPSleep(3);
    // if (Result != 0)
    //     exit(Result);

    while(true)
    {
        Utils::CPSleep(1);
    }

    // system("pause");
    exit(0);
}