#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "ReadSVG.h"

///////// Frame /////////
class myFrame : public wxFrame
{
public:
	myFrame()
		: wxFrame( NULL, -1, "Test", wxDefaultPosition, wxSize( 640, 480 ) )
	{
		auto pnl = new SvgPanel( this );

		wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( pnl, 1, wxEXPAND );
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
		wxImage::AddHandler( new wxPNGHandler );
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )