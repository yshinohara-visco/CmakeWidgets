#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/*
Baseで&myPanelBase::OnButtonとBindした関数OnButtonを子クラスでoverrideした時、
特に再Bindとかせずにそのまま実行した時に実行される処理は？
　→Override後の処理が実行された。余計な心配だった
*/

class myPanelBase : public wxPanel
{
public:
	myPanelBase( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		m_btn = new wxButton( this, wxID_ANY, "myPanelBase" );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( m_btn, 0, wxALIGN_CENTER | wxALL, 10 );
		}
		SetSizer( sizer );

		Bind( wxEVT_BUTTON, &myPanelBase::OnButton, this, m_btn->GetId() );
	}

protected:
	wxButton* m_btn;

private:
	virtual void OnButton( wxCommandEvent& event )
	{
		wxMessageBox( "myPanelBase" );
	}
};


class myPanel1 : public myPanelBase
{
public:
	myPanel1( wxWindow* parent )
		:myPanelBase( parent )
	{
		m_btn->SetLabel( "myPanel1" );
		//再Bindとかはしない
	}

private:
	//OnButtonをoverride
	void OnButton( wxCommandEvent& event ) override
	{
		wxMessageBox( "myPanel1" );
		event.Skip(); //event.Skip()してもBaseの処理は実行されない
	}
};