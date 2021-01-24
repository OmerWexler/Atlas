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
    Singleton<GridNode>::GetInstance().SetName("Server");
    Singleton<GridNode>::GetInstance().AddCollectiveParser(shared_ptr<IParser>((IParser*) DBG_NEW SimpleStringParser()));
    Singleton<GridNode>::GetInstance().AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) DBG_NEW TestCore()));

    int Result;
    Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", "64000");
    if (Result != 0)
    {
        Singleton<GridNode>::GetInstance().Stop();
        exit(Result);
    }

    Utils::CPSleep(5);
    while(Singleton<GridNode>::GetInstance().GetMemberIDs().size() > 0)
    {
        Utils::CPSleep(5);
    }

    Singleton<GridNode>::GetInstance().Stop();
    system("pause");

    return 0;
}