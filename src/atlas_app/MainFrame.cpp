#include "MainFrame.h"
#include "Singleton.h"
#include "Logger.h"
#include "GridNode.h"

#include "wx/xrc/xmlres.h"
#include <wx/tglbtn.h>

using namespace std;

MainFrame::MainFrame()
{
    wxXmlResource::Get()->LoadObject(this, NULL, "Atlas", "wxFrame");
    TargetIP = XRCCTRL(*this, "TargetIP", wxTextCtrl);
    TargetPort = XRCCTRL(*this, "TargetPort", wxTextCtrl);

    NodeNameCtrl = XRCCTRL(*this, "NodeNameCtrl", wxTextCtrl);

    AdminNameDisplay = XRCCTRL(*this, "AdminNameDisplay", wxStaticText);
    ListenAddressDisplay = XRCCTRL(*this, "ListenAddressDisplay", wxStaticText);

    ConnectAsWorkerButton = XRCCTRL(*this, "ConnectAsWorkerButton", wxButton);
    ConnectAsClientButton = XRCCTRL(*this, "ConnectAsClientButton", wxButton);
    SetupOnTargetButton = XRCCTRL(*this, "SetupOnTargetButton", wxButton);
    ReloadNodeButton = XRCCTRL(*this, "ReloadNode", wxButton);

    ConnectAsWorkerButton->Disable();
    ConnectAsClientButton->Disable();
    ReloadNodeButton->Disable();
}

void MainFrame::ConnectUsingCTRLs(bool IsWorker)
{
    Singleton<GridNode>::GetInstance().ConnectToNode(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()), IsWorker);
}

wxDEFINE_EVENT(EVT_NODE_NAME_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_NODE_ADMIN_NAME_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_LISTEN_ADDRESS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_ADMIN_DISCONNECTED, wxCommandEvent);

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( XRCID("ApplyNameButton"), MainFrame::RenameLocalNode )
    EVT_BUTTON ( XRCID("CancelRenameButton"), MainFrame::CancelNodeRename )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_NAME_CHANGED, MainFrame::CancelNodeRename )
    
    EVT_BUTTON ( XRCID("ConnectAsWorkerButton"), MainFrame::ConnectAsWorker )
    EVT_BUTTON ( XRCID("ConnectAsClientButton"), MainFrame::ConnectAsClient )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_ADMIN_NAME_CHANGED, MainFrame::RenameNodeAdmin )
    
    EVT_BUTTON ( XRCID("SetupOnTargetButton"), MainFrame::Setup )
    EVT_COMMAND ( wxID_ANY, EVT_LISTEN_ADDRESS_CHANGED, MainFrame::SetListenAddress )
    
    EVT_BUTTON ( XRCID("ReloadNode"), MainFrame::ReloadNode )

    EVT_COMMAND ( wxID_ANY, EVT_ADMIN_DISCONNECTED, MainFrame::AdminDisconnected )
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

void MainFrame::Setup(wxCommandEvent& event)
{
    Singleton<GridNode>::GetInstance().Setup(string(TargetIP->GetValue().mb_str()), string(TargetPort->GetValue().mb_str()));
    SetupOnTargetButton->Disable();
    ReloadNodeButton->Enable();
    ConnectAsWorkerButton->Enable();
    ConnectAsClientButton->Enable();
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
    Singleton<GridNode>::GetInstance().ReloadNode();

    SetupOnTargetButton->Enable();
    ConnectAsWorkerButton->Disable();
    ConnectAsClientButton->Disable();
    ReloadNodeButton->Disable();
    
    ListenAddressDisplay->SetLabelText("Node is not listening...");
    AdminNameDisplay->SetLabelText("Node is not connected to any admin...");
}

void MainFrame::AdminDisconnected(wxCommandEvent& event)
{
    AdminNameDisplay->SetLabelText("Node is not connected to any admin...");
}