#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/wrapsizer.h>
#include <wx/dcgraph.h>

void DrawCircle( wxDC& dc )
{
	dc.SetPen( *wxRED_PEN );
	dc.SetBrush( *wxBLUE_BRUSH );
	dc.DrawCircle( wxPoint( 100, 100 ), 100 );
}

class myPanelDraw : public wxPanel
{
public:
	myPanelDraw( wxWindow* parent )
		:wxPanel( parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 200 ) )
	{
		SetBackgroundColour( *wxWHITE );
		Bind( wxEVT_PAINT, &myPanelDraw::OnPaint, this );
	}

	void SetDoDraw( std::function<void( wxPaintDC& )> doDraw )
	{
		m_doDraw = doDraw;
	}

private:
	std::function<void( wxPaintDC& )> m_doDraw;

	void OnPaint( wxPaintEvent& event )
	{
		wxPaintDC dc( this );
		dc.Clear();

		if (m_doDraw)
			m_doDraw( dc );
	}
};

class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		SetBackgroundColour( *wxBLACK );
		auto sizer = new wxWrapSizer( wxHORIZONTAL );
		SetSizer( sizer );

		auto addPanel = [&]( std::function<void( wxPaintDC& )> func )
		{
			auto pnl = new myPanelDraw( this );
			pnl->SetDoDraw( func );
			sizer->Add( pnl, 0, wxALL, 5 );
		};

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();

				DrawCircle( dc );
			} );

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();

				dc.SetUserScale( 0.5, 0.5 );
				DrawCircle( dc );
			} );

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();

				dc.SetUserScale( 2, 2 );
				DrawCircle( dc );
			} );

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();

				wxGCDC gcdc( dc );
				gcdc.SetUserScale( 0.5, 0.5 ); //効く
				DrawCircle( gcdc );
			} );

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();
				dc.SetUserScale( 2, 2 ); //効く

				wxGCDC gcdc( dc );
				DrawCircle( gcdc );
			} );

		addPanel( [&]( wxPaintDC& dc )
			{
				dc.Clear();
				dc.SetUserScale( 0.5, 0.5 ); //0.5倍

				wxGCDC gcdc( dc );
				gcdc.SetUserScale( 0.5, 0.5 ); //0.5*0.5=0.25倍
				DrawCircle( gcdc );
			} );

	}
};