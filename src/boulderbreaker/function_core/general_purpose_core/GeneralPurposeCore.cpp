#include <string>

#include "GeneralPurposeCore.h"
#include "GridNode.h"
#include "Singleton.h"
#include "SetNameMessage.h"
#include "RejectNameMessage.h"

#include "MainFrame.h"
#include "AtlasApp.h"

#undef SendMessage

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
        bool IsAdmin = false;

        if (Sender == Singleton<GridNode>::GetInstance().GetAdmin())
        {
            NameAccepted = true;
            IsAdmin = true;
        }
        else if (OriginalName == NewName)
        {
            NameAccepted = true;
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
                    Singleton<Logger>::GetInstance().Info("Rejected request to rename " + OriginalName + " to - " + NewName);
                    NameAccepted = false;
                }

                Iterator++;
            }

            Iterator = Singleton<GridNode>::GetInstance().GetClientsBegin();
            End = Singleton<GridNode>::GetInstance().GetClientsEnd();

            while(Iterator != End)
            {
                if (Iterator->second.GetName() == NewName)
                {
                    Singleton<Logger>::GetInstance().Info("Rejected request to rename " + OriginalName + " to - " + NewName);
                    NameAccepted = false;
                }

                Iterator++;
            }
        }

        if (NameAccepted)
        {
            Sender.SetName(NewName);
            Singleton<Logger>::GetInstance().Info("Renamed " + OriginalName + " to - " + NewName);

            if (IsAdmin) 
            {
                wxCommandEvent* event = new wxCommandEvent(EVT_NODE_ADMIN_NAME_CHANGED);
                event->SetString(wxString(NewName + " (" + Sender.GetHost() + ":" + Sender.GetPort() + ")"));
                wxQueueEvent(wxGetApp().GetMainFrame(), event);
            }
        }
        else
        {
            Sender.SendMessage(unique_ptr<IMessage>((IMessage*) DBG_NEW RejectNameMessage(NewName)));
            Singleton<Logger>::GetInstance().Info("Rejected request to rename " + OriginalName + " to - " + NewName);
        }
    }

    // REJECT NAME
    if (Message->GetType() == RejectNameMessage::TYPE)
    {
        RejectNameMessage* ANMsg = (RejectNameMessage*) Message.get();
        
        string ReturnedName = ANMsg->GetInvalidName();

        size_t TagStart = ReturnedName.find_last_of('(');
        string DuplicateTag, NewName;
        
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
        
        Singleton<GridNode>::GetInstance().SetName(NewName);
    }
}

bool GeneralPurposeCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == SetNameMessage::TYPE ||
            Message->GetType() == RejectNameMessage::TYPE;
}