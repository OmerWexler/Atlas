/////////////////////////////////////////////////////////////////////////////
// Name:        nodeview.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     15/03/2021 13:43:43
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 15/03/2021 13:43:43

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "nodeview.h"

////@begin XPM images

////@end XPM images


/*
 * wxPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( wxPanel, wxPanel )


/*
 * wxPanel event table definition
 */

BEGIN_EVENT_TABLE( wxPanel, wxPanel )

////@begin wxPanel event table entries
////@end wxPanel event table entries

END_EVENT_TABLE()


/*
 * wxPanel constructors
 */

wxPanel::wxPanel()
{
    Init();
}

wxPanel::wxPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * wxPanel creator
 */

bool wxPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin wxPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    SetParent(parent);
    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end wxPanel creation
    return true;
}


/*
 * wxPanel destructor
 */

wxPanel::~wxPanel()
{
////@begin wxPanel destruction
////@end wxPanel destruction
}


/*
 * Member initialisation
 */

void wxPanel::Init()
{
////@begin wxPanel member initialisation
////@end wxPanel member initialisation
}


/*
 * Control creation for wxPanel
 */

void wxPanel::CreateControls()
{    
////@begin wxPanel content construction
    // Generated by DialogBlocks, 15/03/2021 13:43:43 (unregistered)

    if (!wxXmlResource::Get()->LoadPanel(this, GetParent(), wxT("ID_WXPANEL")))
        wxLogError(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
////@end wxPanel content construction

    // Create custom windows not generated automatically here.
////@begin wxPanel content initialisation
////@end wxPanel content initialisation
}


/*
 * Should we show tooltips?
 */

bool wxPanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap wxPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin wxPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end wxPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon wxPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin wxPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end wxPanel icon retrieval
}