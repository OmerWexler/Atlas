#include <string>

#include "GeneralPurposeCore.h"
#include "GridNode.h"
#include "Singleton.h"
#include "SetNameMessage.h"
#include "AcceptNameMessage.h"

string GeneralPurposeCore::GetType() const 
{
    return "GeneralPurposeCore";
}

void GeneralPurposeCore::QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    // SET NAME
    if (Message->GetType() == SetNameMessage::TYPE)
    {
        string NewName = ((SetNameMessage*) Message.get())->GetName();
        string OriginalName = Sender.GetName();
        bool NameAccepted;

        if (OriginalName == NewName)
        {
            NameAccepted = false;
        }
        else
        {
            auto& Iterator = Singleton<GridNode>::GetInstance().GetMembersBegin();
            auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();
            NameAccepted = true;

            while(Iterator != End)
            {
                if (Iterator->second.GetName() == NewName)
                {
                    // Singleton<Logger>::GetInstance().Info("Rejected request to rename " + OriginalName + " to - " + NewName);
                    NameAccepted = false;
                }

                Iterator++;
            }
        }

        Sender.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW AcceptNameMessage(NameAccepted, NewName)));
        if (NameAccepted)
        {
            Sender.SetName(NewName);
            Singleton<Logger>::GetInstance().Info("Renamed " + OriginalName + " to - " + NewName);
        }
        else
        {
            Singleton<Logger>::GetInstance().Info("Rejected request to rename " + OriginalName + " to - " + NewName);
        }
    }

    // ACCEPT NAME
    if (Message->GetType() == AcceptNameMessage::TYPE)
    {
        AcceptNameMessage* ANMsg = (AcceptNameMessage*) Message.get();
        
        bool IsAccepted = ANMsg->IsAccepted();
        string ReturnedName = ANMsg->GetInvalidName();

        size_t TagStart = ReturnedName.find_last_of('(');
        string DuplicateTag, NewName;
        
        if (IsAccepted) 
        {
            Singleton<GridNode>::GetInstance().SetName(ReturnedName);
        }
        else
        {
            if (TagStart > 0 && TagStart < ReturnedName.length())
            {
                DuplicateTag = ReturnedName.substr(TagStart);
            }
            else
            {
                DuplicateTag = "";
            }

            if (DuplicateTag != "" && DuplicateTag[0] == '(' && DuplicateTag[DuplicateTag.length() - 1] == ')')
            {
                try
                {
                    int Num = stoi(DuplicateTag.substr(1, DuplicateTag.length() - 2));
                    DuplicateTag = "(" + to_string(Num + 1) + ")";
                    
                    NewName = ReturnedName.substr(0, TagStart) + DuplicateTag;
                }
                catch (exception)
                {
                    DuplicateTag = "(1)"; 
                    NewName = ReturnedName + DuplicateTag;
                }
            }
            else
            {
                DuplicateTag = "(1)";
                NewName = ReturnedName + DuplicateTag;
            }
            
            Sender.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW SetNameMessage(NewName)));
        }
    }
}

bool GeneralPurposeCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == SetNameMessage::TYPE ||
            Message->GetType() == AcceptNameMessage::TYPE;
}