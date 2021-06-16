#include <memory>

#include "Utils.h"
#include "SendJobParser.h"
#include "SendJobSerializer.h"
#include "SendJobMessage.h"

#include "JobLog.h"

using namespace std;

int TestSendJobMessage() 
{
    SendJobParser Parser = SendJobParser();
    SendJobSerializer Serializer = SendJobSerializer();
    
    vector<Argument> Inputs = vector<Argument>();
    Inputs.push_back(Argument("AAA", false));
    Inputs.push_back(Argument("BB", true));

    shared_ptr<IJob> Job = shared_ptr<IJob>((IJob*) DBG_NEW JobLog());
    Job->Execute(Inputs);
    
    unique_ptr<IMessage> UMsg(ATLS_CREATE_UNIQUE_MSG(SendJobMessage, Job, Inputs, Path("TestPath/"), Job->GetOutput()));
    SendJobMessage* SJMsg = (SendJobMessage*) UMsg.get();

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJSEPBTestPath@@@Job Log@@@0@@@" + Job->GetUniqueDescriptor() + "@@@@@@2@@@AAA@@@0@@@BB@@@1")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        SendJobMessage* SJMsg = (SendJobMessage*) UMsg.get();
        SJMsg->GetJob()->Execute(SJMsg->GetInput());
    }
    else
    {
        return -1;
    }

    return 0;
}
