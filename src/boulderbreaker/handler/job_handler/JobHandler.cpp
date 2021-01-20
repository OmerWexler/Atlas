#include "JobHandler.h"

#include "GridNode.h"

#include "CancelJobMessage.h"

void JobHandler::AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) const
{
    if (!IsMessageRelated(Message))
        return;

    if (Message->GetType() == "CancelJob")
    {
        CancelJobMessage* CJMsg = (CancelJobMessage*) Message.get();
        // Singleton<GridNode>::GetInstance().CancelJob();
    }
    
}

bool JobHandler::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == "CancelJob" ||
            Message->GetType() == "SendJob" ||
            Message->GetType() == "SendJobOutput";
}