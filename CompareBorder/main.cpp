#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextPanel : public wxPanel
{
public:
	TextPanel( wxWindow* parent, wxString string, long style )
		:wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style)
	{
		auto txt = new wxStaticText( this, wxID_ANY, string );
		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( txt, 0, wxALL, 10 );
		}
		SetSizer( sizer );
	}
};

///////// Panel /////////
class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id )
	{
		auto txt = new TextPanel( this, "wxBORDER_NONE", wxBORDER_NONE );
		auto txt2 = new TextPanel( this, "wxBORDER_STATIC", wxBORDER_STATIC );
		auto txt3 = new TextPanel( this, "wxBORDER_SIMPLE", wxBORDER_SIMPLE );
		auto txt4 = new TextPanel( this, "wxBORDER_RAISED", wxBORDER_RAISED );
		auto txt5 = new TextPanel( this, "wxBORDER_SUNKEN", wxBORDER_SUNKEN );
		auto txt6 = new TextPanel( this, "wxBORDER_DOUBLE", wxBORDER_DOUBLE );
		auto txt7 = new TextPanel( this, "wxBORDER_THEME", wxBORDER_THEME );

		auto btnEnable = new wxButton( this, wxID_ANY, "Enable" );
		auto btnRefresh = new wxButton( this, wxID_ANY, "Refresh" );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( txt, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt2, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt3, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt4, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt5, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt6, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( txt7, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( btnEnable, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->Add( btnRefresh, 0, wxALIGN_CENTER | wxALL, 10 );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );

		txt7->Bind( wxEVT_PAINT, [&, txt7]( wxPaintEvent& event )
			{
				wxPaintDC dc( txt7 );
				dc.Clear();
				dc.SetPen( *wxRED );
				if (txt7->IsEnabled())
				{
					dc.DrawRectangle( wxPoint(0,0), txt7->GetClientSize() );
				}
				else
				{
					dc.DrawCircle( wxPoint(5,5), 5 );
				}
			} );

		Bind( wxEVT_BUTTON, [&, txt, txt2, txt3, txt4, txt5, txt6, txt7]( wxCommandEvent& event )
			{
				static bool enable = false;
				txt->Enable( enable );
				txt2->Enable( enable );
				txt3->Enable( enable );
				txt4->Enable( enable );
				txt5->Enable( enable );
				txt5->Enable( enable );
				txt6->Enable( enable );
				txt7->Enable( enable );
				txt->Refresh();
				txt2->Refresh();
				txt3->Refresh();
				txt4->Refresh();
				txt5->Refresh();
				txt5->Refresh();
				txt6->Refresh();
				txt7->Refresh();
				enable = !enable;
			}, btnEnable->GetId() );

		Bind( wxEVT_BUTTON, [&]( wxCommandEvent& event )
			{
				Refresh();
			}, btnRefresh->GetId() );

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
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )