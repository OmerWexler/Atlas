#include "JobCore.h"

#include "Utils.h"
#include "GridNode.h"

#include "CancelJobMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"

string JobCore::GetType() const
{
    return "JobCore";
}

void JobCore::QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    if (!IsMessageRelated(Message))
        return;

    if (Message->GetType() == CancelJobMessage::TYPE)
    {
        CancelJobMessage* CJMsg = (CancelJobMessage*) Message.get();
        string Descriptor = CJMsg->GetDescriptor();
        if (LocalJobs.find(Descriptor) != LocalJobs.end())
        {
            LocalJobs[Descriptor]->Kill();
            while (LocalJobs[Descriptor]->IsAlive())
            {
                Utils::CPSleep(0.1f);
            }
        }
        else 
        {

        }
    }
}

bool JobCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == CancelJobMessage::TYPE ||
           Message->GetType() == SendJobMessage::TYPE ||
           Message->GetType() == SendJobOutputMessage::TYPE;
}