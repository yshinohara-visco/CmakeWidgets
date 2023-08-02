#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/display.h>

///////// Panel /////////
class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY )
		:wxPanel( parent, id )
	{
		auto sizer = new wxBoxSizer( wxVERTICAL );
		SetSizer( sizer );

		auto addButton = [&]( std::function<void( wxCommandEvent& )> func )
		{
			static int count = 0;
			auto btn = new wxButton( this, wxID_ANY, wxString::Format( "btn%d", ++count ) );
			GetSizer()->Add( btn, 0, wxALIGN_CENTER | wxALL, 10 );
			btn->Bind( wxEVT_BUTTON, func );
		};

		addButton( [&]( wxCommandEvent& event )
			{
				auto display = wxDisplay( this );

				//静的
				auto count = display.GetCount();
				//個別
				auto name = display.GetName();
				auto isPrimary = display.IsPrimary();
				auto cArea = display.GetClientArea();
				auto geo = display.GetGeometry();
				auto scale = display.GetScaleFactor();


				wxString str;
				str << "count " << count << "\n";
				str << "name " << name << "\n";
				str << "isPrimary " << isPrimary << "\n";
				str << wxString::Format( "ClientArea %d, %d, %d, %d\n", cArea.x, cArea.y, cArea.width, cArea.height );
				str << wxString::Format( "Geometory %d, %d, %d, %d\n", geo.x, geo.y, geo.width, geo.height );
				str << "scale " << scale << "\n";
				wxMessageBox( str );
			} );

		addButton( [&]( wxCommandEvent& event )
			{
				//Windows:指定無しでShowModaするとフレームの左上から固定値ずらした位置に表示される
				//Linux:フレームの中心に表示される
				auto dialog = wxDialog( this, wxID_ANY, "test1" );
				dialog.ShowModal();
			} );

		addButton( [&]( wxCommandEvent& event )
			{
				//Windows:点0,0に表示される
				//Linux:SetPosition()は無視されフレームの中心に表示される
				auto dialog = wxDialog( this, wxID_ANY, "test1" );
				dialog.SetPosition( wxPoint( 0, 0 ) );
				dialog.ShowModal();
			} );

		addButton( [&]( wxCommandEvent& event )
			{
				//Windows:フレームの中心に表示される
				//Linux:フレームの中心に表示される
				auto dialog = wxDialog( this, wxID_ANY, "test1" );
				dialog.CenterOnParent();
				dialog.ShowModal();
			} );

	}

private:

};
