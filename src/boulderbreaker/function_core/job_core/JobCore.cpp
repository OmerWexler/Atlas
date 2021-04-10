#include "JobCore.h"

#include "GridNode.h"
#include "CancelJobMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"
#include "Path.h"

#include "AtlasApp.h"
#include "MainFrame.h"

#undef GetJob
#undef SendMessage

string JobCore::GetType() const
{
    return "JobCore";
}

void JobCore::HandleMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    if (!IsMessageRelated(Message))
        return;

    string Type = Message->GetType();
    if (Type == CancelJobMessage::TYPE)
    {
        CancelJobMessageFunc(Message, Sender);
    }
    else if (Type == SendJobMessage::TYPE)
    {   
        SendJobMessageFunc(Message, Sender);
    }
    else if (Type == SendJobOutputMessage::TYPE)
    {
        SendJobOutputMessageFunc(Message, Sender);
    }
}

void JobCore::SendJobMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    string CurrentNodeName = Singleton<GridNode>::GetInstance().GetName();
    SendJobMessage* SJMsg = (SendJobMessage*) Message.get();
    Path& PathToTarget = SJMsg->GetPathToTarget();

    if (PathToTarget.size() > 0 && PathToTarget[0] == CurrentNodeName)
    {
        PathToTarget.RemoveFromStart();
        
        if (PathToTarget.size() == 0) // Target is this Node
        {
            shared_ptr<IJob>& Job = SJMsg->GetJob();
            LocalJobs[Job->GetUniqueDescriptor()] = Job;
            Job->StartASync(SJMsg->GetInput());
        }
        else // Target is a member Node
        {   
            int TargetID = -1;
            auto& It = Singleton<GridNode>::GetInstance().GetMembersBegin();
            auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();

            while (It != End)
            {
                if (It->second.GetName() == PathToTarget[0])
                {
                    TargetID = It->first;
                    break;
                }

                It++;
            }

            if (TargetID != -1)
            {
                Singleton<GridNode>::GetInstance().GetMember(TargetID).SendMessage(Message);
            }
            else
            {
                Singleton<Logger>::GetInstance().Warning(
                    "Got a SendJob message with an unmatching path.\nNode name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());
            }
        }
    }
    else
    {
        Singleton<Logger>::GetInstance().Warning(
            "Got a SendJob message with an unmatching path.\n Node name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());
    }
}

void JobCore::CancelJobMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    CancelJobMessage* CJMsg = (CancelJobMessage*) Message.get();
    string Descriptor = CJMsg->GetDescriptor();
    Path& PathToTarget = CJMsg->GetPathToTarget();
    string CurrentNodeName = Singleton<GridNode>::GetInstance().GetName();
 
    if (PathToTarget.size() > 0 && PathToTarget[0] == CurrentNodeName)
    {
        PathToTarget.RemoveFromStart();
        
        if (PathToTarget.size() == 0) // Target is this Node
        {
            if (LocalJobs.find(Descriptor) != LocalJobs.end())
            {
                LocalJobs[Descriptor]->Kill();
            }
        }
        else // Target is a member Node
        {   
            int TargetID = -1;
            auto& It = Singleton<GridNode>::GetInstance().GetMembersBegin();
            auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();

            while (It != End)
            {
                if (It->second.GetName() == PathToTarget[0])
                {
                    TargetID = It->first;
                    break;
                }

                It++;
            }

            if (TargetID != -1)
            {
                Singleton<GridNode>::GetInstance().GetMember(TargetID).SendMessage(Message);
            }
            else
            {
                Singleton<Logger>::GetInstance().Warning(
                    "Got a CancelJob message with an unmatching path.\nNode name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());
            }
        }
    }
    else
    {
        Singleton<Logger>::GetInstance().Warning(
            "Got a CancelJob message with an unmatching path.\nNode name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());    
    }
}

void JobCore::SendJobOutputMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    SendJobOutputMessage* SJOMsg = (SendJobOutputMessage*) Message.get();
    Path& PathToTarget = SJOMsg->GetPathToTarget();
    string CurrentNodeName = Singleton<GridNode>::GetInstance().GetName();

    if (PathToTarget.size() == 1 && PathToTarget[0] == CurrentNodeName) // Current node is owner
    {
        auto& Iterator = Singleton<GridNode>::GetInstance().GetDispatchedJobsBegin();
        auto& End = Singleton<GridNode>::GetInstance().GetDispatchedJobsEnd();
        
        while (Iterator != End)
        {
            if (Iterator->get()->GetUniqueDescriptor() == SJOMsg->GetDescriptor())
            {
                Iterator->get()->SetOutput(SJOMsg->GetOutput());
                Iterator->get()->SetIsDone(true);
                Iterator->get()->SetIsAlive(false);
                break;
            }
            Iterator++;
        }

        if (wxGetApp().GetMainFrame())
        {
            wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_JOB_LIST);
            wxQueueEvent(wxGetApp().GetMainFrame(), event);
        }
    }
    else
    {
        PathToTarget.RemoveFromEnd();
        Singleton<GridNode>::GetInstance().GetAdmin().SendMessage(Message);
    }
}

void JobCore::Periodic() 
{
    ASyncFunctionCore::Periodic();

    auto& It = LocalJobs.begin();

    while (It != LocalJobs.end())
    {
        if (It->second->IsDone())
        {
            auto OutputMsg = ATLS_CREATE_UNIQUE_MSG(SendJobOutputMessage, It->second->GetUniqueDescriptor(), It->second->GetPathToTarget(), It->second->GetOutput());
            QueueMessage(OutputMsg, GridConnection());

            It = LocalJobs.erase(It);
        }
        else
            It++;
    }
}

void JobCore::StopCore()
{
    ASyncFunctionCore::StopCore();
    for (auto& Pair: LocalJobs)
    {
        Pair.second->Kill();
    }
}

bool JobCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == CancelJobMessage::TYPE ||
           Message->GetType() == SendJobMessage::TYPE ||
           Message->GetType() == SendJobOutputMessage::TYPE;
}