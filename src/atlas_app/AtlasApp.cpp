#include "AtlasApp.h"
#include "MainFrame.h"
#include "Utils.h"
#include "Singleton.h"
#include "Logger.h"
#include "GridNode.h"

#include "wx/xrc/xmlres.h"

bool AtlasApp::OnInit()
{
    Utils::SetupMemoryCheck();
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("E:\\Desktop\\2021 Cyber Project\\Atlas\\GUI\\Atlas.xrc");

    frame = new MainFrame();
    frame->Show(true);

    Singleton<Logger>::GetInstance().SetLogLevel(L_DEBUG);
    Singleton<Logger>::GetInstance().SetLogFileName("E:\\Desktop\\2021 Cyber Project\\Atlas\\build\\src\\Debug", "Atlas.txt");

    Singleton<GridNode>::GetInstance().StartNode(); // Init the local GridNode
    return true;
}