#include "AtlasApp.h"
#include "MainFrame.h"
#include "Utils.h"

#include "wx/xrc/xmlres.h"

bool AtlasApp::OnInit()
{
    Utils::SetupMemoryCheck();

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("E:\\Desktop\\2021 Cyber Project\\GUI\\Atlas.xrc");

    MainFrame *frame = new MainFrame();
    frame->Show(true);

    return true;
}