#pragma once

#include <wx/app.h>
#include "MainFrame.h"

class AtlasApp : public wxApp
{
private:
    MainFrame* frame;

public:
    virtual bool OnInit();
    MainFrame* GetMainFrame()
    {
        return frame;
    } 
};

wxDECLARE_APP(AtlasApp);