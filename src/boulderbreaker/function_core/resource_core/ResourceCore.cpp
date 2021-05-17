#include "ResourceCore.h"

#include "SendNodePerformanceMessage.h"
#include "Singleton.h"
#include "GridNode.h"
#include "MainFrame.h"
#include "AtlasApp.h"

string ResourceCore::GetType() const
{
    return "ResourceCore";
}

void ResourceCore::QueueMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    if (Message->GetType() == SendNodePerformanceMessage::TYPE)
    {
        SendNodePerformanceCallback(Message, Sender);
    }
}

void ResourceCore::SendNodePerformanceCallback(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    SendNodePerformanceMessage* SNPMsg = (SendNodePerformanceMessage*) Message.get();
    Sender.SetTopPerformance(SNPMsg->GetNodePerformance());

    Path SenderPath = SNPMsg->GetPath();
    SenderPath.AddToStart(Singleton<GridNode>::GetInstance().GetName());
    
    Sender.SetTopPerformancePath(SenderPath);

    PCPerformance TopPerformance = Singleton<GridNode>::GetInstance().GetNodePerformance();
    Path TopPerformancePath = Path(Singleton<GridNode>::GetInstance().GetName());
    
    auto& Iterator = Singleton<GridNode>::GetInstance().GetMembersBegin();
    auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();
    
    while (Iterator != End)
    {
        if (Iterator->second.GetTopPerformance() > TopPerformance)
        {
            TopPerformance = Iterator->second.GetTopPerformance();
            TopPerformancePath = Iterator->second.GetTopPerformancePath();
        }
        Iterator++;
    }

    Singleton<GridNode>::GetInstance().ReportNewTopPerformance(TopPerformance, TopPerformancePath);
    if (wxGetApp().GetMainFrame())
    {
        wxCommandEvent* event = new wxCommandEvent(EVT_UPDATE_TOP_PERFORMANCE);
        wxQueueEvent(wxGetApp().GetMainFrame(), event);
    }
}


bool ResourceCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == SendNodePerformanceMessage::TYPE;
}   