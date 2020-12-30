#include "CancelJobParser.h"
#include "CancelJobSerializer.h"
#include "CancelJobMessage.h"

using namespace std;

int TestCancelJobMessage() 
{
    CancelJobParser Parser = CancelJobParser();
    CancelJobSerializer Serializer = CancelJobSerializer();
    CancelJobMessage* Msg = new CancelJobMessage("ABCD");

    string SMsg = Serializer.Serialize((IMessage*)Msg);
    if (SMsg != "CJABCD")
    {
        delete Msg;
        return -1;
    }

    if (Parser.CanParse(SMsg))
        Msg = (CancelJobMessage*) Parser.Parse(SMsg);
    else 
    {
        delete Msg;
        return -1;
    }

    if (Msg->GetDescriptor() != "ABCD")
    {
        delete Msg;
        return -1;
    }

    delete Msg;
    return 0;
}
