#include "AtlasApp.h"
#include "MainFrame.h"
#include "Utils.h"
#include "Singleton.h"
#include "Logger.h"

#include "wx/xrc/xmlres.h"

bool AtlasApp::OnInit()
{
    Utils::SetupMemoryCheck();

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("E:\\Desktop\\2021 Cyber Project\\Atlas\\GUI\\Atlas.xrc");
    
    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().SetLogFileName("E:\\Desktop\\2021 Cyber Project\\Atlas\\build\\src\\Debug", "Server.txt");
    
    MainFrame *frame = new MainFrame();
    frame->Show(true);

    return true;
}