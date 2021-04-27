#include <memory>

#include "Utils.h"
#include "CancelJobParser.h"
#include "CancelJobSerializer.h"
#include "CancelJobMessage.h"

using namespace std;

int TestCancelJobMessage() 
{
    CancelJobParser Parser = CancelJobParser();
    CancelJobSerializer Serializer = CancelJobSerializer();
    CancelJobMessage* Msg = DBG_NEW CancelJobMessage("ABC_ABC_ABC_ABC_", "A/");
    
    unique_ptr<IMessage> UMsg((IMessage*) Msg);

    string SMsg = Serializer.Serialize(UMsg);
    if (SMsg != "CJABC_ABC_ABC_ABC_A")
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

    if (Msg->GetDescriptor() != "ABC_ABC_ABC_ABC_")
    {
        return -1;
    }

    return 0;
}
