#include "Utils.h"
#include "SendJobPolicyMessage.h"
#include "SendJobPolicySerializer.h"
#include "SendJobPolicyParser.h"

#include "Logger.h"

using namespace std;

int TestSendJobPolicyMessages() 
{
    SendJobPolicyParser Parser = SendJobPolicyParser();
    SendJobPolicySerializer Serializer = SendJobPolicySerializer();

    SendJobPolicyMessage* Msg = DBG_NEW SendJobPolicyMessage(true);
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SJP1")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (SendJobPolicyMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    if (!Msg->GetPolicy())
    {
        return -1;
    }

    return 0;
}