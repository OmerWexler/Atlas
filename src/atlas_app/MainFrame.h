#pragma once

#include <wx/frame.h>
#include <wx/event.h>

class MainFrame : public wxFrame
{
public:
    MainFrame();
    DECLARE_EVENT_TABLE();

private:
    void ConnectUsingCTRLs(bool IsWorker);

    void RenameLocalNode(wxCommandEvent& event);
    void CancelNodeRename(wxCommandEvent& event);
    void ConnectAsWorker(wxCommandEvent& event);
    void ConnectAsClient(wxCommandEvent& event);
    void Listen(wxCommandEvent& event);
    void ReloadNode(wxCommandEvent& event);
};

wxDECLARE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);