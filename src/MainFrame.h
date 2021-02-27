#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <iostream>

using namespace std;

enum
{
    TEXT_Main = wxID_HIGHEST + 1, // declares an id which will be used to call our button
};

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:

    void OnExit(wxCommandEvent& event);
};