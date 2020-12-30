#include <memory>

#include "CancelJobParser.h"
#include "CancelJobSerializer.h"
#include "CancelJobMessage.h"

using namespace std;

int TestCancelJobMessage() 
{
    CancelJobParser Parser = CancelJobParser();
    CancelJobSerializer Serializer = CancelJobSerializer();
    CancelJobMessage* Msg = new CancelJobMessage("ABCD");
    
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "CJABCD")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (CancelJobMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    if (Msg->GetDescriptor() != "ABCD")
    {
        return -1;
    }

    return 0;
}
