#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/rawbmp.h>
#include <chrono>

namespace
{
	long long Time( std::function<void()> func )
	{
		auto start = std::chrono::system_clock::now();
		func();
		auto end = std::chrono::system_clock::now();

		auto time = end - start;
		auto msec = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
		return msec;
	}
}

///////// Panel /////////
class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id )
	{
		auto txt = new wxStaticText( this, wxID_ANY, "Hello world" );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->AddStretchSpacer();
			sizer->Add( txt, 0, wxALIGN_CENTER );
			sizer->AddStretchSpacer();
		}
		SetSizer( sizer );

		auto addButton = [&, txt]( std::function<wxString()> func )
		{
			static int count = 0;
			auto btn = new wxButton( this, wxID_ANY, wxString::Format( "btn%d", ++count ) );
			GetSizer()->Add( btn, 0, wxALIGN_CENTER | wxALL, 5 );

			btn->Bind( wxEVT_BUTTON, [&, txt, func]( wxCommandEvent& event )
				{
					auto str = func();
					txt->SetLabel( str );
				} );
		};

		addButton( [&]()
			{
				return "test";
			} );
		addButton( [&]()
			{
				//Windowsでは32,ラズパイでは24となった
				wxBitmap bmp( wxSize( 10, 10 ) );
				return wxString::Format( "default depth=%d", bmp.GetDepth() );
			} );
		addButton( [&]()
			{
				//Windowsでは32なのにHasAlphaはfalseだった
				wxBitmap bmp( wxSize( 10, 10 ) );
				bool hasAlpha = bmp.HasAlpha();
				if (hasAlpha)
				{
					bmp.ResetAlpha();
				}
				return wxString::Format( "hasAlpha=%d depth=%d", hasAlpha, bmp.GetDepth() );
			} );
		addButton( [&]()
			{
				//WindowsではwxNativePixelDataを構築できずに落ちる
				//ラズパイではwxAlphaPixwlDataを構築できずに落ちる
				wxBitmap bmp( wxSize( 10, 10 ) );

				wxAlphaPixelData data( bmp );
				wxAlphaPixelData::Iterator p1( data );
				auto s = wxString::Format( "%d", p1.Red() );
				std::cout << s.ToStdString() << std::endl;

				wxNativePixelData data2( bmp );
				wxNativePixelData::Iterator p2( data2 );
				auto s2 = wxString::Format( "%d", p2.Red() );
				std::cout << s2.ToStdString() << std::endl;

				return s + " " + s2;
			} );
		addButton( [&]()
			{
				//wxImageへの変換を挟むよりもPixelDataで処理する方が早い
				//Releaseビルドだと6倍近い差があった　ラズパイでは体感できるくらいの時間がかかる
				//また、明示的に32と指定したならラズパイでもwxAlphaPixelDataを構築できる

				wxBitmap src( wxSize( 1280, 960 ), 32 );
				wxBitmap dst( wxSize( 1280, 960 ), 32 );

				auto func1 = [&]()
				{
					wxAlphaPixelData dSrc( src );
					wxAlphaPixelData dDst( dst );
					wxAlphaPixelData::Iterator pSrc( dSrc );
					wxAlphaPixelData::Iterator pDst( dDst );

					for (size_t i = 0; i < 960; i++)
					{
						pSrc.MoveTo( dSrc, 0, i );
						pDst.MoveTo( dDst, 0, i );
						for (size_t j = 0; j < 1280; j++, pSrc++, pDst++)
						{
							pDst.Alpha() = (pSrc.Red() > 0) ? 70 : 0;
						}
					}
				};

				auto func2 = [&]()
				{
					wxImage iSrc = src.ConvertToImage();
					wxImage iDst = dst.ConvertToImage();
					
					for (size_t i = 0; i < 960; i++)
					{
						for (size_t j = 0; j < 1280; j++)
						{
							iDst.SetAlpha( j, i, (iSrc.GetRed( j, i ) > 0) ? 70 : 0 );
						}
					}
					dst = iDst;
				};

				auto time1 = Time( func1 );
				auto time2 = Time( func2 );

				return wxString::Format( "time1=%lld time2=%lld", time1, time2 );
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
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};
IMPLEMENT_APP( myApp )