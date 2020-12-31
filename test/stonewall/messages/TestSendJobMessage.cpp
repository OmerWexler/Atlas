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
    
    IJob* JobLog = new JobLog();
    JobLog->SetUniqueDescriptor("Test");
    
    SendJobMessage* Msg = new SendJobMessage(
        (IJob*) JobLog,
        Inputs
    );
    
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJSEPB0@@@0@@@Test@@@AAA@@@0@@@BB@@@1")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (SendJobMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    return 0;
}
