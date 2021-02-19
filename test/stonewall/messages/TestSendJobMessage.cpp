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
    Job->SetUniqueDescriptor("Test");
    
    Job->Execute(Inputs);
    
    unique_ptr<IMessage> UMsg((IMessage*) DBG_NEW SendJobMessage(Job, Inputs, "TestPath/", Job->GetOutput()));
    SendJobMessage* SJMsg = (SendJobMessage*) UMsg.get();

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJSEPB0@@@0@@@Test@@@TestPath/@@@2@@@AAA@@@0@@@BB@@@1@@@AAA@@@0@@@BB@@@1")
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
