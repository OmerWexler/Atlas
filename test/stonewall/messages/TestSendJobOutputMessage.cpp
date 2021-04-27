#include <memory>

#include "Utils.h"
#include "SendJobOutputParser.h"
#include "SendJobOutputSerializer.h"
#include "SendJobOutputMessage.h"

#include "JobLog.h"

using namespace std;

int TestSendJobOutputMessage() 
{
    SendJobOutputParser Parser = SendJobOutputParser();
    SendJobOutputSerializer Serializer = SendJobOutputSerializer();
    
    vector<Argument> Output = vector<Argument>();
    Output.push_back(Argument("AAA", false));
    Output.push_back(Argument("BB", true));

    JobLog Job{};
    Job.SetUniqueDescriptor("Test");
    
    unique_ptr<IMessage> UMsg((IMessage*) DBG_NEW SendJobOutputMessage(Job.GetUniqueDescriptor(), Path(), Output));
    SendJobOutputMessage* SJOMsg = (SendJobOutputMessage*) UMsg.get();

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJOSEPBTest@@@@@@AAA@@@0@@@BB@@@1")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        SJOMsg = (SendJobOutputMessage*) UMsg.get();
    }
    else
    {
        return -1;
    }

    return 0;
}
