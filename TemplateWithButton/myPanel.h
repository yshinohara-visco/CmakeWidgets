#pragma once
#include "myPanelBase.h" 
#include "TestPanel.h"

class myPanel : public myPanelBase
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize );
	~myPanel();

private:
	TestPanel* m_pnlTest;

	void OnButton1( wxCommandEvent& event ) override;
	void OnButton2( wxCommandEvent& event ) override;
	void OnButton3( wxCommandEvent& event ) override;
	void OnButton4( wxCommandEvent& event ) override;
	void OnButton5( wxCommandEvent& event ) override;
	void OnButton6( wxCommandEvent& event ) override;
	void OnButton7( wxCommandEvent& event ) override;
	void OnButton8( wxCommandEvent& event ) override;

	void OnCatchInfo( wxCommandEvent& event ) override;
};

