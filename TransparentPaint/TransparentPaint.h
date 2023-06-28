﻿#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/wrapsizer.h>
#include <wx/dcgraph.h>
#include <wx/dcbuffer.h>
#include <memory>

/*

親ウィンドウの描画を残して（透過して）描画するには
1．SetBackgroudStyle(wxBG_STYLE_PAINT)が必要。(Linuxでは不要らしい)
2．dcでclear()を実行してはならない。
3．BufferedDCを使用してはならない。
4．アニメーションのように変化がある描画には向かない

WindowsでBufferedDCを使う時、デフォルトではバッファは各パネルで共通らしい
そのため、clear()をせずにBufferedDCを使うと、他のパネルで最後に描画した内容が写り込む。
*/

class CtrlBase : public wxPanel
{
public:
	CtrlBase( wxWindow* parent, bool stylePaint )
		:wxPanel()
	{
		if (stylePaint)
			SetBackgroundStyle( wxBG_STYLE_PAINT );
		Create( parent, wxID_ANY, wxDefaultPosition, wxSize( 100, 100 ) );

		Bind( wxEVT_PAINT, &CtrlBase::OnPaint, this );
		Bind( wxEVT_LEFT_DOWN, [&]( wxMouseEvent& event )
			{
				Refresh();
			} );
	}

protected:
	void DoPaint( wxDC& dc )
	{
		auto gc = wxGraphicsContext::CreateFromUnknownDC( dc );
		wxGCDC gcdc( gc );
		gcdc.SetPen( wxPen( *wxRED, 5 ) );
		gcdc.SetBrush( *wxTRANSPARENT_BRUSH );
		gcdc.DrawCircle( wxPoint( 50, 50 ), 40 );
	}

private:
	virtual void OnPaint( wxPaintEvent& event ) = 0;
};

class CtrlPaintDC : public CtrlBase
{
public:
	CtrlPaintDC( wxWindow* parent, bool stylePaint )
		:CtrlBase( parent, stylePaint ) {}
private:
	void OnPaint( wxPaintEvent& event )
	{
		wxPaintDC dc( this );
		DoPaint( dc );
	}
};

class CtrlBufferedDC : public CtrlBase
{
public:
	CtrlBufferedDC( wxWindow* parent, bool stylePaint )
		:CtrlBase( parent, stylePaint ) {}
private:
	void OnPaint( wxPaintEvent& event )
	{
		wxPaintDC dc( this );
		wxBufferedDC bdc( &dc );
		DoPaint( bdc );
	}
};

class CtrlBufferedPaintDC : public CtrlBase
{
public:
	CtrlBufferedPaintDC( wxWindow* parent, bool stylePaint )
		:CtrlBase( parent, stylePaint ) {}
private:
	void OnPaint( wxPaintEvent& event )
	{
		wxBufferedPaintDC dc( this );
		DoPaint( dc );
	}
};

class CtrlAutoBufferedPaintDC : public CtrlBase
{
public:
	CtrlAutoBufferedPaintDC( wxWindow* parent, bool stylePaint )
		:CtrlBase( parent, stylePaint ) {}
private:
	void OnPaint( wxPaintEvent& event )
	{
		wxAutoBufferedPaintDC dc( this );
		DoPaint( dc );
	}
};

class CtrlTest : public wxPanel
{
public:
	CtrlTest( wxWindow* parent )
	{
		SetBackgroundStyle( wxBG_STYLE_PAINT );
		Create( parent, wxID_ANY, wxDefaultPosition, wxSize( 100, 100 ) );

		Bind( wxEVT_PAINT, [&]( wxPaintEvent& event )
			{
				wxBufferedPaintDC dc( this );
				dc.Clear();
				dc.DrawRoundedRectangle( GetClientRect(), 20 );
			} );
	}
};


class PanelBack : public wxPanel
{
public:
	PanelBack( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		SetBackgroundColour( *wxCYAN );

		auto sizer = new wxWrapSizer();
		SetSizer( sizer );
		auto add = [&](wxWindow* window)
		{
			sizer->Add( window );
		};

		add( new CtrlPaintDC( this, false ) );
		add( new CtrlPaintDC( this, true ) );
		add( new CtrlBufferedDC( this, false ) );
		add( new CtrlBufferedDC( this, true ) );
		add( new CtrlBufferedPaintDC( this, false ) );
		add( new CtrlBufferedPaintDC( this, true ) );
		add( new CtrlAutoBufferedPaintDC( this, true ) );
		add( new CtrlTest( this ) );


		Bind( wxEVT_PAINT, &PanelBack::OnPaint, this );
		Bind( wxEVT_LEFT_DOWN, [&]( wxMouseEvent& event )
			{
				Refresh();
			} );
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