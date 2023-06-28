#include "myPanel.h"

myPanel::myPanel( wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size )
	:myPanelBase( parent, id, pos, size )
{
	m_pnlTest = new TestPanel( this );

	GetSizer()->Replace( m_TestWindow, m_pnlTest );

	Layout();
}

myPanel::~myPanel()
{

}

void myPanel::OnButton1( wxCommandEvent& event )
{
	m_text1->SetLabel( "button1" );
	m_text1->Refresh();
}

void myPanel::OnButton2( wxCommandEvent& event )
{
	wxCommandEvent evt( myEVT_INFO );
	evt.SetInt( 100 );
	evt.SetString( "event test" );
	ProcessWindowEvent( evt );
}

void myPanel::OnButton3( wxCommandEvent& event )
{
	m_pnlTest->SetBackgroundColour( *wxRED );
	m_pnlTest->Refresh();
}

void myPanel::OnButton4( wxCommandEvent& event ) {}
void myPanel::OnButton5( wxCommandEvent& event ) {}
void myPanel::OnButton6( wxCommandEvent& event ) {}
void myPanel::OnButton7( wxCommandEvent& event ) {}
void myPanel::OnButton8( wxCommandEvent& event ) {}

void myPanel::OnCatchInfo( wxCommandEvent& event )
{
	int n = event.GetInt();
	wxString s = event.GetString();

	m_text2->SetLabel( wxString::Format( "%d", n ) );
	m_text3->SetLabel( s );
}