#include "JobCore.h"

#include "GridNode.h"

#include "CancelJobMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"

string JobCore::GetType() const
{
    return "JobCore";
}

void JobCore::AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    if (!IsMessageRelated(Message))
        return;

    if (Message->GetType() == CancelJobMessage::TYPE)
    {
        CancelJobMessage* CJMsg = (CancelJobMessage*) Message.get();
        // Singleton<GridNode>::GetInstance().CancelJob();
    }
    
}

bool JobCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == CancelJobMessage::TYPE ||
            Message->GetType() == SendJobMessage::TYPE ||
            Message->GetType() == SendJobOutputMessage::TYPE;
}