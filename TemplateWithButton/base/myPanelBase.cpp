#include "myPanelBase.h"

wxDEFINE_EVENT( myEVT_INFO, wxCommandEvent );

myPanelBase::myPanelBase( wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size )
	:wxPanel( parent, id, pos, size )
{
	m_TestWindow = new wxPanel( this );
	m_text1 = new wxStaticText( this, wxID_ANY, "1" );
	m_text2 = new wxStaticText( this, wxID_ANY, "2" );
	m_text3 = new wxStaticText( this, wxID_ANY, "3" );
	m_text4 = new wxStaticText( this, wxID_ANY, "4" );
	m_text5 = new wxStaticText( this, wxID_ANY, "5" );
	m_text6 = new wxStaticText( this, wxID_ANY, "6" );
	m_text7 = new wxStaticText( this, wxID_ANY, "7" );
	m_text8 = new wxStaticText( this, wxID_ANY, "8" );

	m_button1 = new wxButton( this, wxID_ANY, "btn1" );
	m_button2 = new wxButton( this, wxID_ANY, "btn2" );
	m_button3 = new wxButton( this, wxID_ANY, "btn3" );
	m_button4 = new wxButton( this, wxID_ANY, "btn4" );
	m_button5 = new wxButton( this, wxID_ANY, "btn5" );
	m_button6 = new wxButton( this, wxID_ANY, "btn6" );
	m_button7 = new wxButton( this, wxID_ANY, "btn7" );
	m_button8 = new wxButton( this, wxID_ANY, "btn8" );

	wxBoxSizer* sizerV = new wxBoxSizer( wxVERTICAL );
	{
		sizerV->Add( m_TestWindow, 1, wxEXPAND );

		wxBoxSizer* sizerH1 = new wxBoxSizer( wxHORIZONTAL );
		{
			sizerH1->Add( m_text1, 1 );
			sizerH1->Add( m_text2, 1 );
			sizerH1->Add( m_text3, 1 );
			sizerH1->Add( m_text4, 1 );
		}
		sizerV->Add( sizerH1, 0, wxEXPAND );

		wxBoxSizer* sizerH2 = new wxBoxSizer( wxHORIZONTAL );
		{
			sizerH2->Add( m_text5, 1 );
			sizerH2->Add( m_text6, 1 );
			sizerH2->Add( m_text7, 1 );
			sizerH2->Add( m_text8, 1 );
		}
		sizerV->Add( sizerH2, 0, wxEXPAND );

		wxBoxSizer* sizerH3 = new wxBoxSizer( wxHORIZONTAL );
		{
			sizerH3->Add( m_button1, 1 );
			sizerH3->Add( m_button2, 1 );
			sizerH3->Add( m_button3, 1 );
			sizerH3->Add( m_button4, 1 );
		}
		sizerV->Add( sizerH3, 0, wxEXPAND );

		wxBoxSizer* sizerH4 = new wxBoxSizer( wxHORIZONTAL );
		{
			sizerH4->Add( m_button5, 1 );
			sizerH4->Add( m_button6, 1 );
			sizerH4->Add( m_button7, 1 );
			sizerH4->Add( m_button8, 1 );
		}
		sizerV->Add( sizerH4, 0, wxEXPAND );
	}
	this->SetSizer( sizerV );

	m_button1->Bind( wxEVT_BUTTON, &myPanelBase::OnButton1, this );
	m_button2->Bind( wxEVT_BUTTON, &myPanelBase::OnButton2, this );
	m_button3->Bind( wxEVT_BUTTON, &myPanelBase::OnButton3, this );
	m_button4->Bind( wxEVT_BUTTON, &myPanelBase::OnButton4, this );
	m_button5->Bind( wxEVT_BUTTON, &myPanelBase::OnButton5, this );
	m_button6->Bind( wxEVT_BUTTON, &myPanelBase::OnButton6, this );
	m_button7->Bind( wxEVT_BUTTON, &myPanelBase::OnButton7, this );
	m_button8->Bind( wxEVT_BUTTON, &myPanelBase::OnButton8, this );

	Bind( myEVT_INFO, &myPanelBase::OnCatchInfo, this );
}

myPanelBase::~myPanelBase()
{

}