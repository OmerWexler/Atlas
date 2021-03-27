#pragma once

#include <wx/frame.h>
#include <wx/event.h>

class MainFrame : public wxFrame
{
public:
    MainFrame();
    DECLARE_EVENT_TABLE();

private:
    void RenameLocalNode(wxCommandEvent& event);
    void CancelNodeRename(wxCommandEvent& event);
    void ConnectToNode(wxCommandEvent& event);
};

wxDECLARE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);