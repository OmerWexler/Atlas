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
    MemberNamesBox = XRCCTRL(*this, "MemberNamesBox", wxStaticBox);
    ClientNamesBox = XRCCTRL(*this, "ClientNamesBox", wxStaticBox);

    ConnectAsMemberButton = XRCCTRL(*this, "ConnectAsMemberButton", wxButton);
    ConnectAsClientButton = XRCCTRL(*this, "ConnectAsClientButton", wxButton);
    ListenOnTargetButton = XRCCTRL(*this, "ListenOnTargetButton", wxButton);
    ReloadNodeButton = XRCCTRL(*this, "ReloadNode", wxButton);
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

    EVT_COMMAND ( wxID_ANY, EVT_ADMIN_DISCONNECTED, MainFrame::AdminDisconnected )
    EVT_COMMAND ( wxID_ANY, EVT_NODE_CONNECTIONS_CHANGED, MainFrame::ReloadConnectionsDisplay )
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

    ListenOnTargetButton->Enable();
    ConnectAsMemberButton->Enable();
    ConnectAsClientButton->Enable();


    ListenAddressDisplay->SetLabelText("Node is not listening...");
    AdminNameDisplay->SetLabelText("Node is not connected to any admin...");

    ReloadConnectionsDisplay(event);
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
        Banner = new wxStaticText(ClientNamesBox, wxID_ANY, wxString(Iterator->second.GetName()));
        ClientNamesBox->GetContainingSizer()->Add(Banner);
        Iterator++;
    }

    Iterator = Singleton<GridNode>::GetInstance().GetMembersBegin();
    End = Singleton<GridNode>::GetInstance().GetMembersEnd();

    while (Iterator != End)
    {
        Banner = new wxStaticText(MemberNamesBox, wxID_ANY, wxString(Iterator->second.GetName()));
        MemberNamesBox->GetContainingSizer()->Add(Banner);
        Iterator++;
    }

    Fit();
}

bool Close(bool force=false)
{
    Singleton<GridNode>::GetInstance().CloseNode();

    return true;
}