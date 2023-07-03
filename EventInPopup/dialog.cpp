#include "dialog.h"

wxDEFINE_EVENT( myEVT_DIALOG_BUTTON, wxCommandEvent );

myDialog::myDialog( wxWindow* parent )
	:wxDialog( parent, wxID_ANY, "" )
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

	Bind( wxEVT_BUTTON, &myDialog::OnButton1, this, btn1->GetId() );
	Bind( wxEVT_BUTTON, &myDialog::OnButton2, this, btn2->GetId() );
	Bind( wxEVT_BUTTON, &myDialog::OnButton3, this, btn3->GetId() );
	Bind( wxEVT_BUTTON, &myDialog::OnButton4, this, btn4->GetId() );
}

void myDialog::OnButton1( wxCommandEvent& event )
{
	auto evt = wxCommandEvent( myEVT_DIALOG_BUTTON, GetId() );
	evt.SetString( "Button1" );
	ProcessWindowEvent( evt );
}

void myDialog::OnButton2( wxCommandEvent& event )
{
	auto evt = new wxCommandEvent( myEVT_DIALOG_BUTTON, GetId() );
	evt->SetString( "Button2" );
	wxQueueEvent( GetEventHandler(), evt );
}

void myDialog::OnButton3( wxCommandEvent& event )
{
	auto evt = wxCommandEvent( myEVT_DIALOG_BUTTON, GetId() );
	evt.SetString( "Button3" );
	GetParent()->ProcessWindowEvent( evt );
}

void myDialog::OnButton4( wxCommandEvent& event )
{
	auto evt = new wxCommandEvent( myEVT_DIALOG_BUTTON, GetId() );
	evt->SetString( "Button4" );
	wxQueueEvent( GetParent()->GetEventHandler(), evt );
}
