#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Argument.h"

using namespace std;

class MainFrame : public wxFrame
{
public:
    MainFrame();

DECLARE_EVENT_TABLE();

private:
    wxTextCtrl* TargetIP;
    wxTextCtrl* TargetPort;

    wxTextCtrl* NodeNameCtrl;

    wxStaticText* AdminNameDisplay;
    wxStaticText* ListenAddressDisplay;
    wxStaticBox* MemberNamesBox;
    wxStaticBox* ClientNamesBox;
    
    wxButton* ConnectAsMemberButton;
    wxButton* ConnectAsClientButton;
    wxButton* ListenOnTargetButton;
    wxButton* ReloadNodeButton;
    wxButton* SendJobButton;

    wxStaticBox* JobsListSizer;
    wxStaticBox* LocalJobsListSizer;
    wxChoice* JobTypeChoice;
    wxButton* AddArgumentButton;
    wxButton* ClearArgumentButton;
    wxTextCtrl* ArgumentText;
    wxCheckBox* IsArgumentFile;
    wxStaticBox* ArgumentsBox;

    wxStaticText* NodeCPUCores;
    wxStaticText* NodeCPUFrequency;
    wxStaticText* NodeCPULoad;
    wxStaticText* NodeTotalPhysicalMemory;
    wxStaticText* NodeAvailablePhysicalMemory;
    wxStaticText* NodeMemoryLoad;

    wxStaticText* TopCPUCores;
    wxStaticText* TopCPUFrequency;
    wxStaticText* TopCPULoad;
    wxStaticText* TopTotalPhysicalMemory;
    wxStaticText* TopAvailablePhysicalMemory;
    wxStaticText* TopMemoryLoad;
    wxStaticText* TopPath;

    vector<Argument> JobArguments;

    void ConnectUsingCTRLs(bool IsWorker);

    void RenameLocalNode(wxCommandEvent& event);
    void CancelNodeRename(wxCommandEvent& event);
    void ConnectAsWorker(wxCommandEvent& event);
    void ConnectAsClient(wxCommandEvent& event);
    void Listen(wxCommandEvent& event); 
    void SetListenAddress(wxCommandEvent& event); 
    void ReloadNode(wxCommandEvent& event);
    void AdminDisconnected(wxCommandEvent& event);

    void RenameNodeAdmin(wxCommandEvent& event);
    void ReloadConnectionsDisplay(wxCommandEvent& event);
    void UpdateCurrentPerformance(wxCommandEvent& event);
    void UpdateTopPerformance(wxCommandEvent& event);
    void SendJob(wxCommandEvent& event);
    void AddArgument(wxCommandEvent& event);
    void ClearArguments(wxCommandEvent& event);
    void UpdateJobList(wxCommandEvent& event);
    void UpdateLocalJobList(wxCommandEvent& event);

    bool Close(bool force=false);	
};

wxDECLARE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_LISTEN_ADDRESS_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_ADMIN_DISCONNECTED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_CONNECTIONS_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_CURRENT_PERFORMANCE, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_TOP_PERFORMANCE, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_JOB_LIST, wxCommandEvent);
wxDECLARE_EVENT(EVT_UPDATE_LOCAL_JOB_LIST, wxCommandEvent);