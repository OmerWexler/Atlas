#include "SendJobPolicyMessage.h"
#include "SendJobPolicySerializer.h"
#include "SendJobPolicyParser.h"

#include "Logger.h"

using namespace std;

int TestSendJobPolicyMessages() 
{
    SendJobPolicyParser Parser = SendJobPolicyParser();
    SendJobPolicySerializer Serializer = SendJobPolicySerializer();
    SendJobPolicyMessage* Msg = new SendJobPolicyMessage(true);

    string SMsg = Serializer.Serialize((IMessage*)Msg);
    if (SMsg != "SJP1")
    {
        delete Msg;
        return -1;
    }

    if (Parser.CanParse(SMsg))
        Msg = (SendJobPolicyMessage*) Parser.Parse(SMsg);
    else 
    {
        delete Msg;
        return -1;
    }

    if (!Msg->GetPolicy())
    {
        delete Msg;
        return -1;
    }

    delete Msg;
    return 0;
}