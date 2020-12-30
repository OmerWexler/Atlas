#include "SeperatorBasedMessage.h"
#include "SeperatorBasedSerializer.h"
#include "SeperatorBasedParser.h"

using namespace std;

int TestSeperatorBasedMessages() 
{
    SeperatorBasedParser Parser = SeperatorBasedParser();
    SeperatorBasedSerializer Serializer = SeperatorBasedSerializer();
    SeperatorBasedMessage* Msg = new SeperatorBasedMessage();

    Msg->AddValue("AAA");
    Msg->AddValue("BBBB");
    Msg->AddValue("CC");

    string SMsg = Serializer.Serialize((IMessage*)Msg);
    if (SMsg != "SEPBAAA@@@BBBB@@@CC")
    {
        delete Msg;
        return -1;
    }

    if (Parser.CanParse(SMsg))
        Msg = (SeperatorBasedMessage*) Parser.Parse(SMsg);
    else 
    {
        delete Msg;
        return -1;
    }

    vector<string> Values = Msg->GetValues();
    if (Values[0] != "AAA"
        || Values[1] != "BBBB"
        || Values[2] != "CC"
        || Values.size() != 3)
    {
        delete Msg;
        return -1;
    }

    delete Msg;
    return 0;
}