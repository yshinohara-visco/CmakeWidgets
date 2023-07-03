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
		auto sizer = new wxBoxSizer( wxVERTICAL );
		SetSizer( sizer );

		auto addText = [&]( wxFont font )
		{
			auto txt = new wxStaticText( this, wxID_ANY, "Hello world" );
			txt->SetFont( font );
			sizer->Add( txt, 0, wxALIGN_CENTER );
		};

		sizer->AddStretchSpacer();
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "NotoSansCJKjp-Regular" ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "NotoSansCJKjp-Regular" ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "NotoSansCJKjp-Thin" ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "NotoSansCJKjp-Thin" ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "NotoSansMonoCJKjp-Regular" ) );
		addText( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "NotoSansMonoCJKjp-Regular" ) );
		sizer->AddStretchSpacer();
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
		bool success = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Black.otf" );
		bool success1 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Bold.otf" );
		bool success2 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-DemiLight.otf" );
		bool success3 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Light.otf" );
		bool success4 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Medium.otf" );
		bool success5 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Regular.otf" );
		bool success6 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansCJKjp-Thin.otf" );
		bool success7 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansMonoCJKjp-Bold.otf" );
		bool success8 = wxFont::AddPrivateFont( "D:\\NotoSansCJKjp-hinted\\NotoSansMonoCJKjp-Regular.otf" );

		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )