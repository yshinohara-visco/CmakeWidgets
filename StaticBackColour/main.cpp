#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/generic/stattextg.h>
#include <wx/generic/statbmpg.h>


#include <wx/sysopt.h>

///////// Panel /////////

class myCtrl : public wxPanel
{
public:
	myCtrl( wxWindow* parent )
	{
#ifdef __WINDOWS__
		SetBackgroundStyle( wxBG_STYLE_PAINT );
#endif
		Create( parent, wxID_ANY, wxDefaultPosition, wxSize( 300, 300 ), wxFULL_REPAINT_ON_RESIZE );

		auto icon = wxBitmap( 20, 20 );

		auto txt = new wxStaticText( this, -1, "StaticText" );

		auto txtg = new wxGenericStaticText( this, wxID_ANY, "StaticGenericText" );

		auto txt2 = new wxStaticText();
		txt2->SetBackgroundStyle( wxBG_STYLE_PAINT );
		txt2->Create( this, wxID_ANY, "StaticText2" );

		auto txtg2 = new wxGenericStaticText();
		txtg2->SetBackgroundStyle( wxBG_STYLE_PAINT );
		txtg2->Create( this, wxID_ANY, "StaticGenericText2" );

		auto bmp = new wxStaticBitmap( this, -1, icon, wxDefaultPosition, wxSize( 50, 50 ) );

		auto bmpg = new wxGenericStaticBitmap( this, -1, icon, wxDefaultPosition, wxSize( 50, 50 ) );
		
		auto pnl = new wxPanel( this, -1, wxDefaultPosition, wxSize( 50, 50 ) );
		
		auto pnlw = new wxPanel( this, -1, wxDefaultPosition, wxSize( 50, 50 ) );
		pnlw->SetBackgroundColour( *wxWHITE );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( txt, 0, wxALIGN_CENTER );
			sizer->Add( txtg, 0, wxALIGN_CENTER );
			sizer->Add( txt2, 0, wxALIGN_CENTER );
			sizer->Add( txtg2, 0, wxALIGN_CENTER );
			sizer->Add( bmp, 0, wxALIGN_CENTER );
			sizer->Add( bmpg, 0, wxALIGN_CENTER );
			sizer->Add( pnl, 0, wxALIGN_CENTER );
			sizer->Add( pnlw, 0, wxALIGN_CENTER );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );

		Bind( wxEVT_PAINT, &myCtrl::OnPaint, this );
		Bind( wxEVT_LEFT_DOWN, &myCtrl::OnLeftDown, this );
	}

private:
	wxColor m_color = *wxYELLOW;
	void OnPaint( wxPaintEvent& event )
	{
		wxPaintDC dc( this );

		dc.SetPen( *wxBLACK );
		dc.SetBrush( m_color );
		dc.DrawRoundedRectangle( GetClientRect(), 100 );

		
		dc.SetBrush( *wxTRANSPARENT_BRUSH );
		dc.DrawCircle( wxPoint( 50, 50 ), 50 );
	}
	void OnLeftDown( wxMouseEvent& event )
	{
		m_color = (m_color == *wxYELLOW) ? *wxGREEN : *wxYELLOW;
		SetBackgroundColour( m_color );
		Refresh();
	}
};

class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE )
	{
		SetBackgroundColour( *wxCYAN );
		auto ctrl = new myCtrl( this );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( ctrl, 0, wxALIGN_CENTER );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );

		Bind( wxEVT_PAINT, &myPanel::OnPaint, this);
	}
private:
	void OnPaint( wxPaintEvent& event )
	{
		wxPaintDC dc( this );
		dc.Clear();
		auto cSize = GetClientSize();
		for (int i = 0; i * 10 < cSize.x; i++)
		{
			wxColor color = (i % 2) ? GetBackgroundColour() : *wxWHITE;
			dc.SetPen( color );
			dc.SetBrush( color );
			dc.DrawRectangle( wxRect( i * 10, 0, 10, cSize.y ) );
		}
	}
};

///////// Frame /////////
class myFrame : public wxFrame
{
public:
	myFrame()
		: wxFrame( NULL, -1, "Test", wxDefaultPosition, wxSize( 640, 480 ) )
	{
		myPanel* pnl = new myPanel( this );

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
#ifdef __WINDOWS__
		wxSystemOptions::SetOption( wxT( "msw.window.no-clip-children" ), wxT( "1" ) );
#endif
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )