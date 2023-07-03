
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxDECLARE_EVENT( myEVT_DIALOG_BUTTON, wxCommandEvent );

class myDialog : public wxDialog
{
public:
	myDialog( wxWindow* parent );

private:

	void OnButton1( wxCommandEvent& event );
	void OnButton2( wxCommandEvent& event );
	void OnButton3( wxCommandEvent& event );
	void OnButton4( wxCommandEvent& event );

};
