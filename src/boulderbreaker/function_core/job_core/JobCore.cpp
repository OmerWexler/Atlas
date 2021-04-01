#include "JobCore.h"

#include "GridNode.h"
#include "CancelJobMessage.h"
#include "SendJobMessage.h"
#include "SendJobOutputMessage.h"
#include "Path.h"

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
        CancelJobMessage* CJMsg = (CancelJobMessage*) Message.get();
        string Descriptor = CJMsg->GetDescriptor();
        if (LocalJobs.find(Descriptor) != LocalJobs.end())
        {
            LocalJobs[Descriptor]->Kill();
        }
        else 
        {
            Singleton<Logger>::GetInstance().Debug("Couldn't kill job - " + Descriptor);   
        }
    }

    if (Type == SendJobMessage::TYPE)
    {   
        string CurrentNodeName = Singleton<GridNode>::GetInstance().GetName();
        SendJobMessage* SJMsg = (SendJobMessage*) Message.get();
        Path& TargetPath = SJMsg->GetTargetPath();

        if (TargetPath[0] == CurrentNodeName)
        {
            TargetPath.RemoveFromStart();
            
            if (TargetPath.size() == 0) // Target is this Node
            {
                shared_ptr<IJob>& Job = SJMsg->GetJob();
                LocalJobs[Job->GetUniqueDescriptor()] = Job;
                Job->Execute(SJMsg->GetInput());
            }
            else // Target is a member Node
            {   
                int TargetID = -1;
                auto& It = Singleton<GridNode>::GetInstance().GetMembersBegin();
                auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();

                while (It != End)
                {
                    if (It->second.GetName() == TargetPath[0])
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
                        "Got a SendJob message with an unmatching path.\nNode name - " + CurrentNodeName + "\nPath - " + TargetPath.GetStrPath());
                }
            }
        }
        else
        {
            Singleton<Logger>::GetInstance().Warning(
                "Got a SendJob message with an unmatching path.\n Node name - " + CurrentNodeName + "\nPath - " + TargetPath.GetStrPath());
        }
    }
}

void JobCore::Periodic() 
{
    ASyncFunctionCore::Periodic();

    auto& It = LocalJobs.begin();

    while (It != LocalJobs.end())
    {
        if (!It->second->IsAlive())
        {
            Singleton<GridNode>::GetInstance().GetAdmin().SendMessage(
                ATLS_CREATE_UNIQUE_MSG(SendJobOutputMessage, It->second->GetUniqueDescriptor(), It->second->GetOutput())
            );

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