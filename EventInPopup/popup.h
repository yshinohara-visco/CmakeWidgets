

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/popupwin.h>

wxDECLARE_EVENT( myEVT_POPUP_BUTTON, wxCommandEvent );

class myPopup : public wxPopupTransientWindow
{
public:
	myPopup( wxWindow* parent );

private:
	virtual void OnDismiss() override;

	void OnButton1( wxCommandEvent& event );
	void OnButton2( wxCommandEvent& event );
	void OnButton3( wxCommandEvent& event );
	void OnButton4( wxCommandEvent& event );

};
