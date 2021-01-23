#include <memory>
#include <string>
#include <iostream>

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "TestCore.h"

#include "SimpleStringParser.h"

#include "Utils.h"
#include "JobLog.h"

using namespace std;

int main() {
    Utils::SetupMemoryCheck();

    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<GridNode>::GetInstance().SetName("Server");
    Singleton<GridNode>::GetInstance().AddCollectiveParser(shared_ptr<IParser>((IParser*) new SimpleStringParser()));
    Singleton<GridNode>::GetInstance().AddFunctionCore(unique_ptr<IFunctionCore>((IFunctionCore*) new TestCore()));

    int Result;
    Result = Singleton<GridNode>::GetInstance().Setup("127.0.0.1", "64000");
    if (Result != 0)
    {
        Singleton<GridNode>::GetInstance().Stop();
        exit(Result);
    }

    vector<int> IDs;

    Utils::CPSleep(5);
    Singleton<GridNode>::GetInstance().GetMemberIDs(IDs);

    while(IDs.size() > 0)
    {
        Utils::CPSleep(5);
        Singleton<GridNode>::GetInstance().GetMemberIDs(IDs);
    }

    Singleton<GridNode>::GetInstance().Stop();
    system("pause");
    exit(0);
}