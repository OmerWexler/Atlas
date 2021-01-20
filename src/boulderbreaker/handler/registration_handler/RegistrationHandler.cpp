#include "RegistrationHandler.h"

#include "GridNode.h"
#include "SendJobPolicyMessage.h"

void RegistrationHandler::AddMessage(unique_ptr<IMessage>& Message, GridConnection& Sender) const
{
    if (!IsMessageRelated(Message))
        return;

    if (Message->GetType() == "SendJobPolicy")
    {
        SendJobPolicyMessage* SJPMsg = (SendJobPolicyMessage*) Message.get();
        vector<int> IDs;
        Singleton<GridNode>::GetInstance().GetQueuedConnectionIDs(IDs);

        for (int ID: IDs)
        {
            if (Singleton<GridNode>::GetInstance().GetQueuedConnection(ID) == Sender)
            {
                if (SJPMsg->GetPolicy())
                {
                    Singleton<GridNode>::GetInstance().RegisterMemberFromQueue(ID);
                }
                else
                {
                    Singleton<GridNode>::GetInstance().RegisterClientFromQueue(ID);
                }
            }
        }
    }
}

bool RegistrationHandler::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == "SendJobPolicy";
}