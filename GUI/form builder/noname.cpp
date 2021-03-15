///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

Atlas::Atlas( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Assistant") ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	Atlas = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
	Atlas->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma") ) );

	ID_PANEL = new wxPanel( Atlas, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	ID_PANEL->SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY );
	ID_PANEL->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma") ) );
	ID_PANEL->SetBackgroundColour( wxColour( 196, 196, 196 ) );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( ID_PANEL, wxID_ANY, wxT("Config") ), wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxID_STATIC = new wxStaticText( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Node Name"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	wxID_STATIC->SetForegroundColour( wxColour( 0, 0, 0 ) );

	bSizer3->Add( wxID_STATIC, 0, wxALIGN_LEFT|wxALL|wxFIXED_MINSIZE, 4 );

	ID_TEXTCTRL = new wxTextCtrl( wxID_ANY->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( ID_TEXTCTRL, 0, wxEXPAND|wxLEFT|wxRIGHT|wxFIXED_MINSIZE, 6 );


	wxID_ANY->Add( bSizer3, 0, wxEXPAND|wxALL|wxFIXED_MINSIZE, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	ID_BUTTON1 = new wxButton( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );

	ID_BUTTON1->SetDefault();
	bSizer4->Add( ID_BUTTON1, 1, wxEXPAND|wxLEFT|wxTOP|wxBOTTOM|wxFIXED_MINSIZE, 5 );

	ID_BUTTON = new wxButton( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );

	ID_BUTTON->SetDefault();
	bSizer4->Add( ID_BUTTON, 1, wxEXPAND|wxRIGHT|wxTOP|wxBOTTOM|wxFIXED_MINSIZE, 5 );


	wxID_ANY->Add( bSizer4, 0, wxEXPAND|wxALL, 5 );


	bSizer2->Add( wxID_ANY, 0, wxEXPAND|wxALL, 5 );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( ID_PANEL, wxID_ANY, wxT("Connection") ), wxVERTICAL );

	wxID_STATIC = new wxStaticText( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Connected to - <Admin>"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	wxID_STATIC->SetForegroundColour( wxColour( 0, 0, 0 ) );

	wxID_ANY->Add( wxID_STATIC, 0, wxEXPAND|wxALL|wxFIXED_MINSIZE, 4 );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Members") ), wxVERTICAL );

	wxID_STATIC = new wxStaticText( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	wxID_ANY->Add( wxID_STATIC, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxID_STATIC = new wxStaticText( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	wxID_ANY->Add( wxID_STATIC, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	wxID_ANY->Add( wxID_ANY, 0, wxEXPAND|wxALL, 5 );

	m_staticline1 = new wxStaticLine( wxID_ANY->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	wxID_ANY->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );

	wxID_STATIC1 = new wxStaticText( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Target IP"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC1->Wrap( 0 );
	wxID_STATIC1->SetForegroundColour( wxColour( 0, 0, 0 ) );

	bSizer31->Add( wxID_STATIC1, 0, wxALIGN_LEFT|wxALL|wxFIXED_MINSIZE, 4 );

	ID_TEXTCTRL1 = new wxTextCtrl( wxID_ANY->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( ID_TEXTCTRL1, 0, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxLEFT|wxRIGHT, 6 );


	wxID_ANY->Add( bSizer31, 0, wxEXPAND, 5 );

	m_button4 = new wxButton( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_ANY->Add( m_button4, 0, wxALL|wxEXPAND, 5 );


	bSizer2->Add( wxID_ANY, 1, wxALL|wxEXPAND, 5 );


	gSizer1->Add( bSizer2, 0, wxEXPAND|wxALL|wxFIXED_MINSIZE, 0 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 1, 0, 0 );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( ID_PANEL, wxID_ANY, wxT("Parsers") ), wxVERTICAL );


	gSizer2->Add( wxID_ANY, 0, wxEXPAND|wxALL|wxFIXED_MINSIZE, 5 );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( ID_PANEL, wxID_ANY, wxT("Serializers") ), wxVERTICAL );


	gSizer2->Add( wxID_ANY, 0, wxEXPAND|wxALL|wxFIXED_MINSIZE, 5 );


	gSizer1->Add( gSizer2, 0, wxEXPAND|wxALL, 0 );

	wxStaticBoxSizer* wxID_ANY;
	wxID_ANY = new wxStaticBoxSizer( new wxStaticBox( ID_PANEL, wxID_ANY, wxT("Jobs") ), wxVERTICAL );

	wxStaticBoxSizer* JobInterface;
	JobInterface = new wxStaticBoxSizer( new wxStaticBox( wxID_ANY->GetStaticBox(), wxID_ANY, wxT("JobName") ), wxVERTICAL );

	wxID_STATIC = new wxStaticText( JobInterface->GetStaticBox(), wxID_ANY, wxT("Type - <Type>"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	JobInterface->Add( wxID_STATIC, 0, wxALIGN_LEFT|wxALL, 5 );

	wxID_STATIC = new wxStaticText( JobInterface->GetStaticBox(), wxID_ANY, wxT("Is Alive - <IsAlive>"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	JobInterface->Add( wxID_STATIC, 0, wxALIGN_LEFT|wxALL, 5 );

	wxID_STATIC = new wxStaticText( JobInterface->GetStaticBox(), wxID_ANY, wxT("Success - <Success>"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	JobInterface->Add( wxID_STATIC, 0, wxALIGN_LEFT|wxALL, 5 );

	wxID_STATIC = new wxStaticText( JobInterface->GetStaticBox(), wxID_ANY, wxT("Unique Descriptor - <Unique Descriptor>"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC->Wrap( 0 );
	JobInterface->Add( wxID_STATIC, 0, wxALIGN_LEFT|wxALL, 5 );

	ID_BUTTON2 = new wxButton( JobInterface->GetStaticBox(), wxID_ANY, wxT("Kill Job"), wxDefaultPosition, wxDefaultSize, 0 );

	ID_BUTTON2->SetDefault();
	JobInterface->Add( ID_BUTTON2, 0, wxEXPAND|wxALL, 5 );


	wxID_ANY->Add( JobInterface, 0, wxALL|wxEXPAND, 5 );


	gSizer1->Add( wxID_ANY, 0, wxEXPAND|wxALL, 5 );


	ID_PANEL->SetSizer( gSizer1 );
	ID_PANEL->Layout();
	gSizer1->Fit( ID_PANEL );
	Atlas->AddPage( ID_PANEL, wxT("Home Node"), true );

	bSizer1->Add( Atlas, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

Atlas::~Atlas()
{
}
