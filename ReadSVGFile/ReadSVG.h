#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SvgPanel : public wxPanel
{
public:
	SvgPanel( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		//static関数FromSVGFile()の返り値を使う
		auto bmp = wxBitmapBundle::FromSVGFile( "test.svg", wxSize(50,50) );
		auto bmp2 = wxBitmapBundle::FromSVGFile( "testtest.svg", wxSize(20,20) );
		//1枚のpngから作った場合は？
		auto bmp3 = wxBitmapBundle::FromFiles( "icon.png" );

		//サイズが変わっても綺麗
		auto sbmp = new wxStaticBitmap( this, wxID_ANY, bmp );
		auto sbmp2 = new wxStaticBitmap( this, wxID_ANY, bmp2 );
		auto sbmp3 = new wxStaticBitmap( this, wxID_ANY, bmp2.GetBitmap(wxSize(100, 100)) );
		//auto sbmp4 = new wxStaticBitmap( this, wxID_ANY, bmp2.GetBitmap(wxSize(1000, 1000)) );
		
		//pngから作った場合、単に引き延ばした汚い画像が表示される svgを使う価値がある
		auto sbmp5 = new wxStaticBitmap( this, wxID_ANY, bmp3 );
		auto sbmp6 = new wxStaticBitmap( this, wxID_ANY, bmp3.GetBitmap(wxSize(200,200)) );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( sbmp, 0, wxALIGN_CENTER );
			sizer->Add( sbmp2, 0, wxALIGN_CENTER );
			sizer->Add( sbmp3, 0, wxALIGN_CENTER );
			//sizer->Add( sbmp4, 0, wxALIGN_CENTER );
			sizer->Add( sbmp5, 0, wxALIGN_CENTER );
			sizer->Add( sbmp6, 0, wxALIGN_CENTER );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );
		Layout();
	}

private:
};