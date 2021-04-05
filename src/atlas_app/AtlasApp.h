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
        if (this && frame)
            return frame;
        else
            return nullptr;
    } 
};

wxDECLARE_APP(AtlasApp);