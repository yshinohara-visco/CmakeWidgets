#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "panel.h"

///////// Frame /////////
class myFrame : public wxFrame
{
public:
	myFrame()
		: wxFrame( NULL, -1, "Test", wxDefaultPosition, wxSize( 640, 480 ) )
	{
		myPanelBase* pnl = new myPanelBase( this );
		myPanelBase* pnl1 = new myPanel1( this );

		wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( pnl, 1, wxEXPAND );
			sizer->Add( pnl1, 1, wxEXPAND );
		}
		SetSizer( sizer );
	}
};

///////// APP /////////
class myApp : public wxApp
{
public:
	virtual bool OnInit()
	{
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )