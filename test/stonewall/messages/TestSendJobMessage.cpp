#include <memory>

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
    
    IJob* Job = new JobLog();
    Job->SetSuccess(1);
    Job->SetUniqueDescriptor("Test");
    
    unique_ptr<IMessage> UMsg((IMessage*) new SendJobMessage((IJob*) Job, Inputs));

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJSEPB0@@@1@@@Test@@@AAA@@@0@@@BB@@@1")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
    }
    else
    {
        return -1;
    }

    return 0;
}
