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
		SetBackgroundColour( *wxCYAN );
		//Windowsの場合、α付きBitmapファイルでもファイルから読み込んで表示すると透明度はなくなるらしい
		//Linuxの場合、imgBmpを除いて透明度有りで表示された　ファイルからの取得でも違うのか
		auto bmpBmp = wxBitmap( "RGB.bmp", wxBITMAP_TYPE_BMP );
		auto bmpPng = wxBitmap( "RGB.png", wxBITMAP_TYPE_PNG );
		auto bundleBmp = wxBitmapBundle::FromFiles( "RGB.bmp" );
		auto bundlePng = wxBitmapBundle::FromFiles( "RGB.png" );
		auto imgBmp = wxImage( "RGB.bmp", wxBITMAP_TYPE_BMP );
		auto imgPng = wxImage( "RGB.png", wxBITMAP_TYPE_PNG );

		Bind( wxEVT_PAINT, [&, bmpBmp, bmpPng, bundleBmp, bundlePng, imgBmp, imgPng]( wxPaintEvent& event )
			{
				wxPaintDC dc( this );

				dc.DrawBitmap( bmpBmp, wxPoint( 0, 0 ) );
				dc.DrawBitmap( bmpPng, wxPoint( 100, 0 ) );
				dc.DrawBitmap( bundleBmp.GetBitmap(wxSize(100,100)), wxPoint(0, 100));
				dc.DrawBitmap( bundlePng.GetBitmap( wxSize( 100, 100 ) ), wxPoint( 100, 100 ) );
				dc.DrawBitmap( imgBmp, wxPoint( 0, 200 ) );
				dc.DrawBitmap( imgPng, wxPoint( 100, 200 ) );
			} );
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
		wxInitAllImageHandlers();
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )