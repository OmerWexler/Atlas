#include "Utils.h"
#include "SeperatorBasedMessage.h"
#include "SeperatorBasedSerializer.h"
#include "SeperatorBasedParser.h"

using namespace std;

int TestSeperatorBasedMessages() 
{
    SeperatorBasedParser Parser = SeperatorBasedParser();
    SeperatorBasedSerializer Serializer = SeperatorBasedSerializer();
    SeperatorBasedMessage* Msg = DBG_NEW SeperatorBasedMessage();

    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    Msg->AddValue("AAA");
    Msg->AddValue("BBBB");
    Msg->AddValue("CC");

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "SEPBAAA@@@BBBB@@@CC")
    {
        return -1;
    }

    if (Parser.CanParse(SMsg))
    {
        Parser.Parse(SMsg, UMsg);
        Msg = (SeperatorBasedMessage*) UMsg.get();
    }
    else 
    {
        return -1;
    }

    vector<string> Values = Msg->GetValues();
    if (Values[0] != "AAA"
        || Values[1] != "BBBB"
        || Values[2] != "CC"
        || Values.size() != 3)
    {
        return -1;
    }

    return 0;
}