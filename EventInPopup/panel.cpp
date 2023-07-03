#include "panel.h"
#include "popup.h"
#include "dialog.h"

myPanel::myPanel( wxWindow* parent, wxWindowID id )
	:wxPanel( parent, id )
{
	m_txtCtrl = new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_btnPopup = new wxButton( this, wxID_ANY, "popup" );
	m_btnDialog = new wxButton( this, wxID_ANY, "dialog" );
	m_btnClear = new wxButton( this, wxID_ANY, "clear" );

	auto sizer = new wxBoxSizer( wxVERTICAL );
	{
		sizer->AddStretchSpacer();
		sizer->Add( m_txtCtrl, 1, wxEXPAND | wxALL, 10 );

		auto sizerButton = new wxBoxSizer( wxHORIZONTAL );
		{
			sizerButton->Add( m_btnPopup );
			sizerButton->AddSpacer( 10 );
			sizerButton->Add( m_btnDialog );
			sizerButton->AddSpacer( 10 );
			sizerButton->Add( m_btnClear );
		}
		sizer->Add( sizerButton, 0, wxALIGN_CENTER );
		sizer->AddStretchSpacer();
	}
	SetSizer( sizer );

	Bind( wxEVT_BUTTON, &myPanel::OnButtonPopup, this, m_btnPopup->GetId() );
	Bind( wxEVT_BUTTON, &myPanel::OnButtonDialog, this, m_btnDialog->GetId() );
	Bind( wxEVT_BUTTON, &myPanel::OnButtonClear, this, m_btnClear->GetId() );
	Bind( myEVT_POPUP_BUTTON, &myPanel::OnPopupButton, this );
	Bind( myEVT_DIALOG_BUTTON, &myPanel::OnDialogButton, this );
}

void myPanel::OnButtonPopup( wxCommandEvent& event )
{
	m_txtCtrl->AppendText( "Popup\n" );
	auto popup = new myPopup( this );
	popup->Position( m_btnPopup->GetScreenPosition(), wxSize( 0, 0 ) );
	popup->Popup();
}

void myPanel::OnButtonDialog( wxCommandEvent& event )
{
	m_txtCtrl->AppendText( "Dialog\n" );
	auto dialog = new myDialog( this );
	dialog->Show();
	//解放してない
}

void myPanel::OnButtonClear( wxCommandEvent& event )
{
	m_txtCtrl->Clear();
}

void myPanel::OnPopupButton( wxCommandEvent& event )
{
	m_txtCtrl->AppendText( event.GetString() + "\n" );
}

void myPanel::OnDialogButton( wxCommandEvent& event )
{
	m_txtCtrl->AppendText( event.GetString() + "\n" );
}
