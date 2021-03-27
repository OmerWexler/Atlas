#include "MainFrame.h"
#include "Singleton.h"
#include "Logger.h"
#include "GridNode.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/xrc/xmlres.h"
#include <wx/tglbtn.h>

using namespace std;

MainFrame::MainFrame()
{
    wxXmlResource::Get()->LoadObject(this, NULL, "Atlas", "wxFrame");
}

wxDEFINE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( XRCID("ApplyNameButton"), MainFrame::RenameLocalNode )
    EVT_BUTTON ( XRCID("CancelRenameButton"), MainFrame::CancelNodeRename )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_NAME_CHANGED, MainFrame::CancelNodeRename )
END_EVENT_TABLE()

void MainFrame::RenameLocalNode(wxCommandEvent& event)
{
    wxTextCtrl* NodeName = XRCCTRL(*this, "NodeNameCtrl", wxTextCtrl);
    Singleton<GridNode>::GetInstance().SetName(string(NodeName->GetValue().mb_str()));
    Singleton<Logger>::GetInstance().Debug(Singleton<GridNode>::GetInstance().GetName());
}

void MainFrame::CancelNodeRename(wxCommandEvent& event)
{
    wxTextCtrl* NodeName = XRCCTRL(*this, "NodeNameCtrl", wxTextCtrl);
    NodeName->SetValue(wxString(Singleton<GridNode>::GetInstance().GetName()));
    Singleton<Logger>::GetInstance().Debug(Singleton<GridNode>::GetInstance().GetName());
}

void MainFrame::ConnectToNode(wxCommandEvent& event)
{
    wxTextCtrl* ConnectionTarget = XRCCTRL(*this, "ConnectionTarget", wxTextCtrl);
    wxToggleButton* IsWorker = XRCCTRL(*this, "IsWorkerToggle", wxToggleButton);
    Singleton<GridNode>::GetInstance().ConnectToNode(string(ConnectionTarget->GetValue().mb_str()), DEFAULT_NODE_CONNECTION_PORT, IsWorker->GetValue());
}