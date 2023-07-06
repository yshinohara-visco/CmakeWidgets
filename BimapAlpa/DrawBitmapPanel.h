#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/rawbmp.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <memory>

namespace
{
	wxBitmap MakeBitmap( int r, int g, int b, int alpha )
	{
		wxSize size( 100, 100 );
		wxBitmap bmp( size, 32 );
		wxAlphaPixelData data( bmp );
		wxAlphaPixelData::Iterator it( data );
		for (size_t y = 0; y < size.y; y++)
		{
			it.MoveTo( data, 0, y );
			for (size_t x = 0; x < size.x; x++)
			{
				it.Red() = r;
				it.Green() = g;
				it.Blue() = b;
				it.Alpha() = alpha;
				it++;
			}
		}
		return bmp;
	}

	auto bmp1 = MakeBitmap( 255, 50, 50, 20 );
	auto bmp2 = MakeBitmap( 50, 255, 50, 20 );
	auto bmp3 = MakeBitmap( 50, 50, 255, 20 );

	void DrawBitmaps( wxDC& dc )
	{
		dc.Clear();

		dc.DrawBitmap( bmp1, wxPoint( 25, 0 ) );
		dc.DrawBitmap( bmp2, wxPoint( 0, 50 ) );
		dc.DrawBitmap( bmp3, wxPoint( 50, 50 ) );
	}

	void DrawBitmaps( std::unique_ptr<wxGraphicsContext>& gc )
	{
		gc->DrawBitmap( bmp1, 25, 0, 100, 100 );
		gc->DrawBitmap( bmp2, 0, 50, 100, 100 );
		gc->DrawBitmap( bmp3, 50, 50, 100, 100 );
	}
}

class DrawBitmapPanel : public wxPanel
{
public:
	DrawBitmapPanel( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		SetBackgroundColour( wxColor( 150, 150, 150 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxPaintDC dc( this );
				DrawBitmaps( dc );
			} );
	}
};

class DrawBitmapPanel2 : public wxPanel
{
public:
	DrawBitmapPanel2( wxWindow* parent )
		:wxPanel()
	{
		SetBackgroundStyle( wxBG_STYLE_PAINT );
		Create( parent, wxID_ANY );

		SetBackgroundColour( wxColor( 150, 150, 150 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxAutoBufferedPaintDC dc( this );
				// Same result with the following DC
				//wxPaintDC pdc( this );
				//wxBufferedDC dc( &pdc );
				//wxBufferedPaintDC dc( this );
				DrawBitmaps( dc );
			} );
	}
};

class DrawBitmapPanel3 : public wxPanel
{
public:
	DrawBitmapPanel3( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		SetBackgroundColour( wxColor( 150, 150, 150 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxPaintDC dc( this );
				wxGCDC gdc( dc );
				DrawBitmaps( gdc );
			} );
	}
};

class DrawBitmapPanel4 : public wxPanel
{
public:
	DrawBitmapPanel4( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		SetBackgroundColour( wxColor( 150, 150, 150 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxPaintDC dc( this );
				std::unique_ptr<wxGraphicsContext> gc( wxGraphicsContext::Create( dc ) );

				dc.Clear();
				DrawBitmaps( gc );
			} );
	}
};

class DrawBitmapPanel5 : public wxPanel
{
public:
	DrawBitmapPanel5( wxWindow* parent )
		:wxPanel()
	{
		SetBackgroundStyle( wxBG_STYLE_PAINT );
		Create( parent, wxID_ANY );

		SetBackgroundColour( wxColor( 150, 150, 150 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxAutoBufferedPaintDC dc( this );
				std::unique_ptr<wxGraphicsContext> gc( wxGraphicsContext::Create( dc ) );

				dc.Clear();
				DrawBitmaps( gc );
			} );
	}
};