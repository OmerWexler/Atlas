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

void MainFrame::ConnectUsingCTRLs(bool IsWorker)
{
    wxTextCtrl* TargetIP = XRCCTRL(*this, "TargetIP", wxTextCtrl);
    wxTextCtrl* TargetPort = XRCCTRL(*this, "TargetPort", wxTextCtrl);
    Singleton<GridNode>::GetInstance().ConnectToNode(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()), IsWorker);
}

wxDEFINE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( XRCID("ApplyNameButton"), MainFrame::RenameLocalNode )
    EVT_BUTTON ( XRCID("CancelRenameButton"), MainFrame::CancelNodeRename )
    EVT_BUTTON ( XRCID("ConnectAsWorkerButton"), MainFrame::ConnectAsWorker )
    EVT_BUTTON ( XRCID("ConnectAsClientButton"), MainFrame::ConnectAsClient )
    EVT_BUTTON ( XRCID("ListenOnTargetButton"), MainFrame::Listen )
    EVT_BUTTON ( XRCID("ReloadNode"), MainFrame::ReloadNode )
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
    wxTextCtrl* TargetIP = XRCCTRL(*this, "TargetIP", wxTextCtrl);
    wxTextCtrl* TargetPort = XRCCTRL(*this, "TargetPort", wxTextCtrl);
    Singleton<GridNode>::GetInstance().Setup(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()));
}

void MainFrame::ReloadNode(wxCommandEvent& event)
{
    Singleton<GridNode>::GetInstance().ReloadNode();
}