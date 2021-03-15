#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace std;

class MainFrame : public wxFrame
{
public:
    MainFrame();
    DECLARE_EVENT_TABLE()

private:
    void RenameLocalNode(wxCommandEvent& event);
};