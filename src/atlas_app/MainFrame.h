#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

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

    wxButton* ConnectAsWorkerButton;
    wxButton* ConnectAsClientButton;
    wxButton* SetupOnTargetButton;

    void ConnectUsingCTRLs(bool IsWorker);

    void RenameLocalNode(wxCommandEvent& event);
    void CancelNodeRename(wxCommandEvent& event);
    void ConnectAsWorker(wxCommandEvent& event);
    void ConnectAsClient(wxCommandEvent& event);
    void Setup(wxCommandEvent& event); 
    void SetListenAddress(wxCommandEvent& event); 
    void ReloadNode(wxCommandEvent& event);

    void RenameNodeAdmin(wxCommandEvent& event);
};

wxDECLARE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_LISTEN_ADDRESS_CHANGED, wxCommandEvent);