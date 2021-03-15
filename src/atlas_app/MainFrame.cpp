#include "MainFrame.h"
#include "Singleton.h"
#include "Logger.h"
#include "GridNode.h"

#include "wx/xrc/xmlres.h"

using namespace std;

MainFrame::MainFrame()
{
    wxXmlResource::Get()->LoadObject(this, NULL, "Atlas", "wxFrame");
}

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( XRCID("ApplyNameButton"), MainFrame::RenameLocalNode )
END_EVENT_TABLE()

void MainFrame::RenameLocalNode(wxCommandEvent& event)
{
    wxTextCtrl* NodeName = XRCCTRL(*this, "NodeNameCtrl", wxTextCtrl);
    Singleton<GridNode>::GetInstance().SetName(string(NodeName->GetValue().mb_str()));
    Singleton<Logger>::GetInstance().Debug(Singleton<GridNode>::GetInstance().GetName());
}