#include <iostream>

#include "MainFrame.h"
#include "wx/xrc/xmlres.h"

using namespace std;

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Atlas")
{
    wxXmlResource::Get()->LoadPanel(this, wxString("Home"));
    
    // wxMenu *menuFile = new wxMenu;
    // menuFile->AppendSeparator();
    // menuFile->Append(wxID_EXIT);

    // wxMenuBar *menuBar = new wxMenuBar;
    // menuBar->Append(menuFile, "&File");
    
    // wxSplitterWindow *MainSizer = new wxSplitterWindow(this);
    // MainSizer->SetSashSize(10);

    // SetMenuBar( menuBar );
    // CreateStatusBar();

    // Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}