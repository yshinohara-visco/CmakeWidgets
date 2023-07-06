#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/rawbmp.h>
#include <wx/dcbuffer.h>

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

	void DrawBitmaps( wxDC& dc )
	{
		dc.Clear();

		auto bmp1 = MakeBitmap( 255, 50, 50, 20 );
		dc.DrawBitmap( bmp1, wxPoint( 25, 0 ) );

		auto bmp2 = MakeBitmap( 50, 255, 50, 20 );
		dc.DrawBitmap( bmp2, wxPoint( 0, 50 ) );

		auto bmp3 = MakeBitmap( 50, 50, 255, 20 );
		dc.DrawBitmap( bmp3, wxPoint( 50, 50 ) );
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
