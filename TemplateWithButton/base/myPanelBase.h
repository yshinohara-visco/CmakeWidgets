#pragma once
#include <wx/wx.h>

wxDECLARE_EVENT( myEVT_INFO, wxCommandEvent );

class myPanelBase : public wxPanel
{
public:
	myPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize );
	~myPanelBase();

protected:
	wxWindow* m_TestWindow;

	wxStaticText* m_text1;
	wxStaticText* m_text2;
	wxStaticText* m_text3;
	wxStaticText* m_text4;
	wxStaticText* m_text5;
	wxStaticText* m_text6;
	wxStaticText* m_text7;
	wxStaticText* m_text8;

	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;
	wxButton* m_button4;
	wxButton* m_button5;
	wxButton* m_button6;
	wxButton* m_button7;
	wxButton* m_button8;

	virtual void OnButton1( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton2( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton3( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton4( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton5( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton6( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton7( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnButton8( wxCommandEvent& event ) { event.Skip(); }

	virtual void OnCatchInfo(wxCommandEvent& event) {}
};