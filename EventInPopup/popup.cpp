#include "popup.h"

wxDEFINE_EVENT( myEVT_POPUP_BUTTON, wxCommandEvent );

myPopup::myPopup( wxWindow* parent )
	:wxPopupTransientWindow( parent, wxBORDER_SIMPLE )
{
	auto sizer = new wxBoxSizer( wxVERTICAL );
	SetSizer( sizer );

	int count = 0;
	auto addButton = [&]()
	{
		auto btn = new wxButton( this, wxID_ANY, wxString::Format( "btn%d", ++count ) );
		sizer->Add( btn, 0, wxALL, 10 );
		return btn;
	};

	auto btn1 = addButton(); //自作イベントProcess
	auto btn2 = addButton(); //自作イベントQueue
	auto btn3 = addButton(); //自作イベント親にProcess
	auto btn4 = addButton(); //自作イベント親にQueue
	Fit();

	Bind( wxEVT_BUTTON, &myPopup::OnButton1, this, btn1->GetId() );
	Bind( wxEVT_BUTTON, &myPopup::OnButton2, this, btn2->GetId() );
	Bind( wxEVT_BUTTON, &myPopup::OnButton3, this, btn3->GetId() );
	Bind( wxEVT_BUTTON, &myPopup::OnButton4, this, btn4->GetId() );
}

void myPopup::OnDismiss()
{
	Destroy();
}

void myPopup::OnButton1( wxCommandEvent& event )
{
	auto evt = wxCommandEvent( myEVT_POPUP_BUTTON, GetId() );
	evt.SetString( "Button1" );
	ProcessWindowEvent( evt );
}

void myPopup::OnButton2( wxCommandEvent& event )
{
	auto evt = new wxCommandEvent( myEVT_POPUP_BUTTON, GetId() );
	evt->SetString( "Button2" );
	wxQueueEvent( GetEventHandler(), evt );
}

void myPopup::OnButton3( wxCommandEvent& event )
{
	auto evt = wxCommandEvent( myEVT_POPUP_BUTTON, GetId() );
	evt.SetString( "Button3" );
	GetParent()->ProcessWindowEvent( evt );
}

void myPopup::OnButton4( wxCommandEvent& event )
{
	auto evt = new wxCommandEvent( myEVT_POPUP_BUTTON, GetId() );
	evt->SetString( "Button4" );
	wxQueueEvent( GetParent()->GetEventHandler(), evt );
}
