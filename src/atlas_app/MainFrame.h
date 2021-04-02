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
    wxStaticBox* MemberNamesBox;
    wxStaticBox* ClientNamesBox;

    wxButton* ConnectAsMemberButton;
    wxButton* ConnectAsClientButton;
    wxButton* ListenOnTargetButton;
    wxButton* ReloadNodeButton;

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

    bool Close(bool force=false);	
};

wxDECLARE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_LISTEN_ADDRESS_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_ADMIN_DISCONNECTED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_CONNECTIONS_CHANGED, wxCommandEvent);