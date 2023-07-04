#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

///////// Panel /////////
class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id )
	{
		auto txt = new wxStaticText( this, wxID_ANY, "Text1" );
		txt->SetBackgroundColour( *wxRED );
		auto txt2 = new wxStaticText( this, wxID_ANY, "Text2" );
		txt2->SetBackgroundColour( *wxBLUE );
		auto txt3 = new wxStaticText( this, wxID_ANY, "Text3" );
		txt3->SetBackgroundColour( *wxGREEN );
		auto txt4 = new wxStaticText( this, wxID_ANY, "Text4" );
		txt4->SetBackgroundColour( *wxYELLOW );
		txt4->SetMinSize( wxSize( 50, -1 ) );
		txt4->SetMaxSize( wxSize( 200, -1 ) );
		auto txt5 = new wxStaticText( this, wxID_ANY, "Text5" );
		txt5->SetBackgroundColour( *wxCYAN );
		auto txt6 = new wxStaticText( this, wxID_ANY, "Text6" );
		txt6->SetBackgroundColour( *wxLIGHT_GREY );
		txt6->SetMinSize( wxSize(50, -1) );
		txt6->SetMaxSize( wxSize( 200, -1 ) );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( txt, 1, wxSTRETCH_NOT );
			sizer->Add( txt2, 1, wxSHRINK );
			sizer->Add( txt3, 2, wxGROW );
			sizer->Add( txt4, 2, wxEXPAND );
			sizer->Add( txt5, 3, wxSHAPED );
			sizer->Add( txt6, 3, wxTILE );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );
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