#include <memory>
#include <string>

#include "Logger.h"

#include "GridConnection.h"
#include "GridNode.h"

#include "RequestBestNodeSerializer.h"
#include "RequestBestNodeParser.h"
#include "RequestBestNodeMessage.h"
#include "SeperatorBasedMessage.h"
#include "SimpleStringMessage.h"

#define _CRTDBG_MAP_ALLOC
#pragma comment(lib, "user32.lib")

using namespace std;

int main() {
    {
        unique_ptr<IMessage> ptr((IMessage*) new SimpleStringMessage(""));
        ptr.reset((IMessage*) new RequestBestNodeMessage(5, PCPerformance()));
    }

    if (_CrtDumpMemoryLeaks()) 
    {
        return -1;
    }
    else 
    {
        return 0;
    }
}