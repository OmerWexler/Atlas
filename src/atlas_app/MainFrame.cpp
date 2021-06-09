#include "MainFrame.h"
#include "Singleton.h"
#include "Logger.h"
#include "GridNode.h"
#include "JobWait.h"
#include "Utils.h"
#include "CancelJobMessage.h"

#include "wx/xrc/xmlres.h"
#include <wx/tglbtn.h>
#include <wx/popupwin.h>

#undef GetJob

#include "JobRegistry.h"

using namespace std;

MainFrame::MainFrame()
{
    wxXmlResource::Get()->LoadObject(this, NULL, "Atlas", "wxFrame");
    TargetIP = XRCCTRL(*this, "TargetIP", wxTextCtrl);
    TargetPort = XRCCTRL(*this, "TargetPort", wxTextCtrl);

    NodeNameCtrl = XRCCTRL(*this, "NodeNameCtrl", wxTextCtrl);

    AdminNameDisplay = XRCCTRL(*this, "AdminNameDisplay", wxStaticText);
    ListenAddressDisplay = XRCCTRL(*this, "ListenAddressDisplay", wxStaticText);
    MemberNamesBox = XRCCTRL(*this, "MemberNamesBox", wxStaticBox);
    ClientNamesBox = XRCCTRL(*this, "ClientNamesBox", wxStaticBox);

    ConnectAsMemberButton = XRCCTRL(*this, "ConnectAsMemberButton", wxButton);
    ConnectAsClientButton = XRCCTRL(*this, "ConnectAsClientButton", wxButton);
    ListenOnTargetButton = XRCCTRL(*this, "ListenOnTargetButton", wxButton);
    ReloadNodeButton = XRCCTRL(*this, "ReloadNode", wxButton);
    SendJobButton = XRCCTRL(*this, "SendJobButton", wxButton);
    JobsListSizer = XRCCTRL(*this, "JobsListSizer", wxStaticBox);
    LocalJobsListSizer = XRCCTRL(*this, "LocalJobsListSizer", wxStaticBox);

    JobTypeChoice = XRCCTRL(*this, "JobTypeChoice", wxChoice);
    
    vector<wxString> JobList{};
    JobList.push_back("Job Log");
    JobList.push_back("Job Wait");
    JobList.push_back("Job Subprocess");
    JobTypeChoice->Set(JobList);

    AddArgumentButton = XRCCTRL(*this, "AddArgumentButton", wxButton);
    ClearArgumentButton = XRCCTRL(*this, "ClearArgumentButton", wxButton);
    ArgumentText = XRCCTRL(*this, "ArgumentText", wxTextCtrl);
    IsArgumentFile = XRCCTRL(*this, "IsArgumentFile", wxCheckBox);
    ArgumentsBox = XRCCTRL(*this, "ArgumentsBox", wxStaticBox);

    NodeCPUCores = XRCCTRL(*this, "NodeCPUCores", wxStaticText);
    NodeCPUFrequency = XRCCTRL(*this, "NodeCPUFrequency", wxStaticText);
    NodeCPULoad = XRCCTRL(*this, "NodeCPULoad", wxStaticText);
    NodeTotalPhysicalMemory = XRCCTRL(*this, "NodeTotalPhysicalMemory", wxStaticText);
    NodeAvailablePhysicalMemory = XRCCTRL(*this, "NodeAvailablePhysicalMemory", wxStaticText);
    NodeMemoryLoad = XRCCTRL(*this, "NodeMemoryLoad", wxStaticText);

    TopCPUCores = XRCCTRL(*this, "TopCPUCores", wxStaticText);
    TopCPUFrequency = XRCCTRL(*this, "TopCPUFrequency", wxStaticText);
    TopCPULoad = XRCCTRL(*this, "TopCPULoad", wxStaticText);
    TopTotalPhysicalMemory = XRCCTRL(*this, "TopTotalPhysicalMemory", wxStaticText);
    TopAvailablePhysicalMemory = XRCCTRL(*this, "TopAvailablePhysicalMemory", wxStaticText);
    TopMemoryLoad = XRCCTRL(*this, "TopMemoryLoad", wxStaticText);
    TopPath = XRCCTRL(*this, "TopPath", wxStaticText);
}

void MainFrame::ConnectUsingCTRLs(bool IsWorker)
{
    Singleton<GridNode>::GetInstance().ConnectToNode(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()), IsWorker);
    ConnectAsMemberButton->Disable();
    ConnectAsClientButton->Disable();
}

wxDEFINE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_LISTEN_ADDRESS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_ADMIN_DISCONNECTED, wxCommandEvent);
wxDEFINE_EVENT(EVT_NODE_CONNECTIONS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_UPDATE_CURRENT_PERFORMANCE, wxCommandEvent);
wxDEFINE_EVENT(EVT_UPDATE_TOP_PERFORMANCE, wxCommandEvent);
wxDEFINE_EVENT(EVT_UPDATE_JOB_LIST, wxCommandEvent);
wxDEFINE_EVENT(EVT_UPDATE_LOCAL_JOB_LIST, wxCommandEvent);

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( XRCID("ApplyNameButton"), MainFrame::RenameLocalNode )
    EVT_BUTTON ( XRCID("CancelRenameButton"), MainFrame::CancelNodeRename )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_NAME_CHANGED, MainFrame::CancelNodeRename )
    
    EVT_BUTTON ( XRCID("ConnectAsMemberButton"), MainFrame::ConnectAsWorker )
    EVT_BUTTON ( XRCID("ConnectAsClientButton"), MainFrame::ConnectAsClient )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_ADMIN_NAME_CHANGED, MainFrame::RenameNodeAdmin )
    
    EVT_BUTTON ( XRCID("ListenOnTargetButton"), MainFrame::Listen )
    EVT_COMMAND ( wxID_ANY, EVT_LISTEN_ADDRESS_CHANGED, MainFrame::SetListenAddress )
    
    EVT_BUTTON ( XRCID("ReloadNode"), MainFrame::ReloadNode )

    EVT_BUTTON ( XRCID("SendJobButton"), MainFrame::SendJob )
    EVT_BUTTON ( XRCID("AddArgumentButton"), MainFrame::AddArgument )
    EVT_BUTTON ( XRCID("ClearArgumentButton"), MainFrame::ClearArguments )

    EVT_COMMAND ( wxID_ANY, EVT_ADMIN_DISCONNECTED, MainFrame::AdminDisconnected )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_CONNECTIONS_CHANGED, MainFrame::ReloadConnectionsDisplay )
    EVT_COMMAND ( wxID_ANY, EVT_UPDATE_CURRENT_PERFORMANCE, MainFrame::UpdateCurrentPerformance )
    EVT_COMMAND ( wxID_ANY, EVT_UPDATE_TOP_PERFORMANCE, MainFrame::UpdateTopPerformance )
    EVT_COMMAND ( wxID_ANY, EVT_UPDATE_JOB_LIST, MainFrame::UpdateJobList )
    EVT_COMMAND ( wxID_ANY, EVT_UPDATE_LOCAL_JOB_LIST, MainFrame::UpdateLocalJobList )
END_EVENT_TABLE()

void MainFrame::RenameLocalNode(wxCommandEvent& event)
{
    Singleton<GridNode>::GetInstance().SetName(string(NodeNameCtrl->GetValue().mb_str()));
}

void MainFrame::CancelNodeRename(wxCommandEvent& event)
{
    NodeNameCtrl->SetValue(wxString(Singleton<GridNode>::GetInstance().GetName()));
}

void MainFrame::ConnectAsClient(wxCommandEvent& event)
{
    ConnectUsingCTRLs(false);
}

void MainFrame::ConnectAsWorker(wxCommandEvent& event)
{
    ConnectUsingCTRLs(true);
}

void MainFrame::Listen(wxCommandEvent& event)
{
    Singleton<GridNode>::GetInstance().Listen(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()));
    ListenOnTargetButton->Disable();
}

void MainFrame::SetListenAddress(wxCommandEvent& event)
{
    ListenAddressDisplay->SetLabelText("Listening on - " + string(event.GetString().mb_str()));
}

void MainFrame::RenameNodeAdmin(wxCommandEvent& event)
{
    AdminNameDisplay->SetLabelText("Connected to - " + string(event.GetString().mb_str()));
}

void MainFrame::ReloadNode(wxCommandEvent& event)
{
    Singleton<GridNode>::GetInstance().CloseNode();
    Singleton<GridNode>::GetInstance().StartNode();

    ListenOnTargetButton->Enable();
    ConnectAsMemberButton->Enable();
    ConnectAsClientButton->Enable();


    ListenAddressDisplay->SetLabelText("Node is not listening...");
    AdminNameDisplay->SetLabelText("Node is not connected to any admin...");

    ReloadConnectionsDisplay(event);
    UpdateJobList(event);
}

void MainFrame::AdminDisconnected(wxCommandEvent& event)
{
    AdminNameDisplay->SetLabelText("Node is not connected to any admin...");
}

void MainFrame::ReloadConnectionsDisplay(wxCommandEvent& event)
{
    ClientNamesBox->GetContainingSizer()->Clear(true);
    MemberNamesBox->GetContainingSizer()->Clear(true);
    Fit();

    wxStaticText* Banner;
    auto& Iterator = Singleton<GridNode>::GetInstance().GetClientsBegin();
    auto& End = Singleton<GridNode>::GetInstance().GetClientsEnd();

    while (Iterator != End)
    {  
        Banner = DBG_NEW wxStaticText(ClientNamesBox, wxID_ANY, wxString(Iterator->second.GetName()));
        ClientNamesBox->GetContainingSizer()->Add(Banner);
        Iterator++;
    }

    Iterator = Singleton<GridNode>::GetInstance().GetMembersBegin();
    End = Singleton<GridNode>::GetInstance().GetMembersEnd();

    while (Iterator != End)
    {
        Banner = DBG_NEW wxStaticText(MemberNamesBox, wxID_ANY, wxString(Iterator->second.GetName()));
        MemberNamesBox->GetContainingSizer()->Add(Banner);
        Iterator++;
    }

    Fit();
}

void MainFrame::UpdateCurrentPerformance(wxCommandEvent& event)
{
    PCPerformance NodePerformance = Singleton<GridNode>::GetInstance().GetNodePerformance(); 

    NodeCPUCores->SetLabelText(
        "CPU Cores - " + to_string(NodePerformance.CPUPerformance.Cores));

    NodeCPUFrequency->SetLabelText(
        "CPU Frequency - " + to_string(NodePerformance.CPUPerformance.FrequencyHZ) + "HZ");

    NodeCPULoad->SetLabelText(
        "CPU Load - " + to_string(NodePerformance.CPUPerformance.CPULoad) + "%");

    NodeTotalPhysicalMemory->SetLabelText(
        "Total Physical Memory - " + to_string(Utils::BytesToMegabytes(NodePerformance.RAMPerformance.TotalPhysicalBytes)) + "MB");

    NodeAvailablePhysicalMemory->SetLabelText(
        "Available Physical Memory - " + to_string(Utils::BytesToMegabytes(NodePerformance.RAMPerformance.AvailablePhysicalBytes)) + "MB");

    NodeMemoryLoad->SetLabelText(
        "Memory Load - " + to_string(NodePerformance.RAMPerformance.MemoryLoad) + "%");

}

void MainFrame::UpdateTopPerformance(wxCommandEvent& event)
{
    PCPerformance TopPerformance = Singleton<GridNode>::GetInstance().GetGridTopPerformance(); 
    Path TopPathObj = Singleton<GridNode>::GetInstance().GetTopPerformancePath(); 

    TopCPUCores->SetLabelText(
        "CPU Cores - " + to_string(TopPerformance.CPUPerformance.Cores));

    TopCPUFrequency->SetLabelText(
        "CPU Frequency - " + to_string(TopPerformance.CPUPerformance.FrequencyHZ) + "HZ");

    TopCPULoad->SetLabelText(
        "CPU Load - " + to_string(TopPerformance.CPUPerformance.CPULoad) + "%");

    TopTotalPhysicalMemory->SetLabelText(
        "Total Physical Memory - " + to_string(Utils::BytesToMegabytes(TopPerformance.RAMPerformance.TotalPhysicalBytes)) + "MB");

    TopAvailablePhysicalMemory->SetLabelText(
        "Available Physical Memory - " + to_string(Utils::BytesToMegabytes(TopPerformance.RAMPerformance.AvailablePhysicalBytes)) + "MB");

    TopMemoryLoad->SetLabelText(
        "Memory Load - " + to_string(TopPerformance.RAMPerformance.MemoryLoad) + "%");

    TopPath->SetLabelText("Node Path (relative) - \"" + TopPathObj.GetStrPath() + "\"");
}

void MainFrame::ClearArguments(wxCommandEvent& event)
{
    JobArguments.clear();
    ArgumentsBox->GetContainingSizer()->Clear(true);
    ArgumentsBox->GetContainingSizer()->Layout();
    Layout();
    Fit();
}

void MainFrame::AddArgument(wxCommandEvent& event)
{
    string ArgumentValue = string(ArgumentText->GetValue().mb_str());
    bool IsFile = IsArgumentFile->GetValue();

    JobArguments.push_back(Argument(ArgumentValue, IsFile));
    
    string ArgumentDescription = "";
    ArgumentDescription += ArgumentValue;

    if (IsFile)
        ArgumentDescription += " (File)";

    ArgumentsBox->GetContainingSizer()->Add(
        DBG_NEW wxStaticText(ArgumentsBox, wxID_ANY, ArgumentDescription), 
        0, wxGROW|wxALL, 2
    );
    ArgumentsBox->GetContainingSizer()->Layout();
    Layout();
    Fit();
}

void MainFrame::SendJob(wxCommandEvent& event)
{
    shared_ptr<IJob> Job;
    
    bool JobFound = JobRegistry::GetJob(string(JobTypeChoice->GetStringSelection().mb_str()), Job);
    if (!JobFound)
        return;

    if (Job->IsInputValid(JobArguments))
    {
        Singleton<GridNode>::GetInstance().SendJobToMembers(
            Job,
            JobArguments
        );

        JobArguments.clear();
        ArgumentsBox->GetContainingSizer()->Clear(true);
        Fit();
    }
}

void MainFrame::UpdateJobList(wxCommandEvent& event)
{
    auto& Iterator = Singleton<GridNode>::GetInstance().GetDispatchedJobsBegin();
    auto& End = Singleton<GridNode>::GetInstance().GetDispatchedJobsEnd();
    
    JobsListSizer->GetContainingSizer()->Clear(true);
    Fit();
    wxPanel* JobBanner = nullptr;

    while (Iterator != End)
    {
        wxStaticBoxSizer* Sizer = DBG_NEW wxStaticBoxSizer(wxVERTICAL, JobsListSizer, wxString(Iterator->get()->GetType()));
        string Descriptor = Iterator->get()->GetUniqueDescriptor();

        Sizer->Add(DBG_NEW wxStaticText(JobsListSizer, wxID_ANY, "Unique Descriptor - " + Descriptor), 0, wxGROW|wxALL, 4);

        string Status;
        if (Iterator->get()->IsDone())
        {
            Status = "Job Done";
        }
        else
        {
            Status = "Running...";
        }

        Sizer->Add(DBG_NEW wxStaticText(JobsListSizer, wxID_ANY, "Status - " + Status), 0, wxGROW|wxALL, 4);
        Sizer->Add(DBG_NEW wxStaticText(JobsListSizer, wxID_ANY, "Owner - " + Iterator->get()->GetPathToTarget().GetStrPath()), 0, wxGROW|wxALL, 4);

        if (Iterator->get()->IsDone())
        {
            Sizer->Add(DBG_NEW wxStaticText(JobsListSizer, wxID_ANY, "Output:"), 0, wxGROW|wxALL, 4);
            
            wxArrayString Outputs = wxArrayString();
            for (auto Output: Iterator->get()->GetOutput())
            {
                string OutputStr = Output.Value;
                if (Output.IsFile)
                    OutputStr += " (File)";

                Outputs.Add(OutputStr);
            }

            wxListBox* OutputBox = DBG_NEW wxListBox(JobsListSizer, wxID_ANY, wxDefaultPosition, wxDefaultSize, Outputs);

            Sizer->Add(OutputBox, 0, wxGROW|wxALL, 4);

            wxButton* DismissJob = DBG_NEW wxButton(JobsListSizer, wxID_ANY, "Dismiss");
            DismissJob->Bind(
                wxEVT_BUTTON,
                [ Descriptor ] (wxCommandEvent&) {
                    Singleton<GridNode>::GetInstance().RemoveJob(Descriptor);
                }
            );
            Sizer->Add(DismissJob, 0, wxGROW|wxALL, 4);
        }
        else 
        {
            wxButton* KillJobButton = DBG_NEW wxButton(JobsListSizer, wxID_ANY, "Kill Job");
            KillJobButton->Bind(
                wxEVT_BUTTON, 
                [ Iterator, Descriptor ] (wxCommandEvent&) { 
                    Singleton<GridNode>::GetInstance().RouteMessageToSelf(
                        ATLS_CREATE_UNIQUE_MSG(CancelJobMessage, Descriptor, Iterator->get()->GetPathToTarget().GetStrPath()),
                        GridConnection()
                    );
                }
            );
            Sizer->Add(KillJobButton, 0, wxGROW|wxALL, 4);
        }
        
        JobsListSizer->GetContainingSizer()->Add(Sizer, 0, wxGROW|wxALL, 4);
        JobsListSizer->GetContainingSizer()->Layout();
        Iterator++;
    }

    Fit();
}

void MainFrame::UpdateLocalJobList(wxCommandEvent& event)
{
    auto& Iterator = Singleton<GridNode>::GetInstance().GetLocalJobsBegin();
    auto& End = Singleton<GridNode>::GetInstance().GetLocalJobsEnd();
    
    LocalJobsListSizer->GetContainingSizer()->Clear(true);
    wxPanel* JobBanner = nullptr;

    while (Iterator != End)
    {
        wxStaticBoxSizer* Sizer = DBG_NEW wxStaticBoxSizer(wxVERTICAL, LocalJobsListSizer, wxString(Iterator->get()->GetType()));
        string Descriptor = Iterator->get()->GetUniqueDescriptor();
        
        Sizer->Add(DBG_NEW wxStaticText(LocalJobsListSizer, wxID_ANY, "Unique Descriptor - " + Descriptor), 0, wxGROW|wxALL, 4);

        string Status;
        if (Iterator->get()->IsDone())
        {
            Status = "Job Done";
        }
        else
        {
            Status = "Running...";
        }

        Sizer->Add(DBG_NEW wxStaticText(LocalJobsListSizer, wxID_ANY, "Status - " + Status), 0, wxGROW|wxALL, 4);
        Sizer->Add(DBG_NEW wxStaticText(LocalJobsListSizer, wxID_ANY, "Owner - " + Iterator->get()->GetPathToTarget().GetStrPath()), 0, wxGROW|wxALL, 4);

        if (Iterator->get()->IsDone())
        {
            Sizer->Add(DBG_NEW wxStaticText(LocalJobsListSizer, wxID_ANY, "Output:"), 0, wxGROW|wxALL, 4);
            
            wxArrayString Outputs = wxArrayString();
            for (auto Output: Iterator->get()->GetOutput())
            {
                string OutputStr = Output.Value;
                if (Output.IsFile)
                    OutputStr += " (File)";

                Outputs.Add(OutputStr);
            }

            wxListBox* OutputBox = DBG_NEW wxListBox(LocalJobsListSizer, wxID_ANY, wxDefaultPosition, wxDefaultSize, Outputs);

            Sizer->Add(OutputBox, 0, wxGROW|wxALL, 4);

            wxButton* DismissJob = DBG_NEW wxButton(LocalJobsListSizer, wxID_ANY, "Dismiss");
            DismissJob->Bind(
                wxEVT_BUTTON,
                [ Descriptor ] (wxCommandEvent&) {
                    Singleton<GridNode>::GetInstance().RemoveLocalJob(Descriptor);
                }
            );
            Sizer->Add(DismissJob, 0, wxGROW|wxALL, 4);
        }
        else 
        {
            wxButton* KillJobButton = DBG_NEW wxButton(LocalJobsListSizer, wxID_ANY, "Kill Job");
            KillJobButton->Bind(
                wxEVT_BUTTON, 
                [ Iterator, Descriptor ] (wxCommandEvent&) { 
                    Singleton<GridNode>::GetInstance().RouteMessageToSelf(
                        ATLS_CREATE_UNIQUE_MSG(CancelJobMessage, Descriptor, Iterator->get()->GetPathToTarget().GetStrPath()),
                        GridConnection()
                    );
                }
            );
            Sizer->Add(KillJobButton, 0, wxGROW|wxALL, 4);
        }
        
        LocalJobsListSizer->GetContainingSizer()->Add(Sizer, 0, wxGROW|wxALL, 4);
        LocalJobsListSizer->GetContainingSizer()->Layout();
        Iterator++;
    }

    Fit();
}

bool MainFrame::Close(bool force)
{
    Singleton<GridNode>::GetInstance().CloseNode();
    return true;
}