/////////////////////////////////////////////////////////////////////////////
// Name:        nodeview.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     15/03/2021 13:43:43
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 15/03/2021 13:43:43

#ifndef _NODEVIEW_H_
#define _NODEVIEW_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_WXPANEL 10000
#define SYMBOL_WXPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_WXPANEL_TITLE _("NodeView")
#define SYMBOL_WXPANEL_IDNAME ID_WXPANEL
#define SYMBOL_WXPANEL_SIZE wxSize(400, 300)
#define SYMBOL_WXPANEL_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * wxPanel class declaration
 */

class wxPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( wxPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    wxPanel();
    wxPanel( wxWindow* parent, wxWindowID id = SYMBOL_WXPANEL_IDNAME, const wxPoint& pos = SYMBOL_WXPANEL_POSITION, const wxSize& size = SYMBOL_WXPANEL_SIZE, long style = SYMBOL_WXPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_WXPANEL_IDNAME, const wxPoint& pos = SYMBOL_WXPANEL_POSITION, const wxSize& size = SYMBOL_WXPANEL_SIZE, long style = SYMBOL_WXPANEL_STYLE );

    /// Destructor
    ~wxPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin wxPanel event handler declarations
////@end wxPanel event handler declarations

////@begin wxPanel member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end wxPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin wxPanel member variables
////@end wxPanel member variables
};

#endif
    // _NODEVIEW_H_
