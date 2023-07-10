#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/rawbmp.h>

#include "DrawBitmapPanel.h"

namespace
{
	const int width = 100;
	const int height = 100;
	wxSize size( width, height );
	int length = width * height;
	wxRect rect( 0, 0, width, height );

	wxBitmap Test1()
	{
		wxImage img( size );
		img.SetRGB( rect, 255, 0, 0 );
		return wxBitmap( img );
	}

	wxBitmap Test2()
	{
		wxImage img;
		img.Create( size );
		img.InitAlpha();

		img.SetRGB( rect, 0, 255, 0 );
		memset( img.GetAlpha(), 70, length );

		return wxBitmap( img );
	}

	wxBitmap Test3()
	{
		wxImage img;
		img.Create( size );
		img.InitAlpha();

		//Windowsでは何故かAlphaを0にすると真っ黒になる Linuxでは透明
		img.SetRGB( rect, 0, 255, 0 );
		memset( img.GetAlpha(), 0, length );
		//順番を変えても一緒だった
		//memset( img.GetAlpha(), 0, length );
		//img.SetRGB( rect, 0, 255, 0 );

		return wxBitmap( img );
	}

	wxBitmap Test4()
	{
		wxBitmap bmp( size, 32 );

		wxAlphaPixelData data( bmp );
		wxAlphaPixelData::Iterator it( data );

		//WindowsではAlphaを0にすると緑ではあるが完全に不透明になる Linuxでは透明
		for (size_t i = 0; i < height; i++)
		{
			it.MoveTo( data, 0, i );
			for (size_t j = 0; j < width; j++)
			{
				it.Red() = 0;
				it.Green() = 255;
				it.Blue() = 0;
				it.Alpha() = 0;
				it++;
			}
		}
		return bmp;
	}

	wxBitmap Test5()
	{
		wxBitmap bmp( size, 32 );

		wxAlphaPixelData data( bmp );
		wxAlphaPixelData::Iterator it( data );

		for (size_t i = 0; i < height; i++)
		{
			it.MoveTo( data, 0, i );
			for (size_t j = 0; j < width; j++)
			{
				it.Red() = 0;
				it.Green() = 255;
				it.Blue() = 0;
				it.Alpha() = 0;
				it++;
			}
		}

		//部分的にでもAlphaが0でなくなれば他は透明になるらしい
		it.MoveTo( data, 50, 50 );
		it.Alpha() = 255;

		return bmp;
	}

}

///////// Panel /////////
class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id )
	{
		auto sbmp = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( sbmp, 0, wxALIGN_CENTER );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );

		auto addButton = [&, sbmp]( std::function<wxBitmap()> func )
		{
			static int count = 0;
			auto btn = new wxButton( this, wxID_ANY, wxString::Format( "btn%d", ++count ) );
			GetSizer()->Add(btn, 0, wxALIGN_CENTER | wxALL, 5);
			btn->Bind( wxEVT_BUTTON, [&, sbmp, func]( wxCommandEvent& event )
				{
					sbmp->SetBitmap( func() );
					Layout();
				});
		};

		addButton( &Test1 );
		addButton( &Test2 );
		addButton( &Test3 );
		addButton( &Test4 );
		addButton( &Test5 );
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
		DrawBitmapPanel* pnl1 = new DrawBitmapPanel( this );
		DrawBitmapPanel2* pnl2 = new DrawBitmapPanel2( this );
		DrawBitmapPanel3* pnl3 = new DrawBitmapPanel3( this );
		DrawBitmapPanel4* pnl4 = new DrawBitmapPanel4( this );
		DrawBitmapPanel5* pnl5 = new DrawBitmapPanel5( this );

		wxBoxSizer* sizer = new wxBoxSizer( wxHORIZONTAL );
		{
			sizer->Add( pnl, 1, wxEXPAND );
			sizer->Add( pnl1, 1, wxEXPAND );
			sizer->Add( pnl2, 1, wxEXPAND );
			sizer->Add( pnl3, 1, wxEXPAND );
			sizer->Add( pnl4, 1, wxEXPAND );
			sizer->Add( pnl5, 1, wxEXPAND );
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