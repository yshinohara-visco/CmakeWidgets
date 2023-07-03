
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class myPanel : public wxPanel
{
public:
	myPanel( wxWindow* parent, wxWindowID id = wxID_ANY );

private:
	wxTextCtrl* m_txtCtrl;
	wxButton* m_btnPopup;
	wxButton* m_btnDialog;
	wxButton* m_btnClear;

	void OnButtonPopup( wxCommandEvent& event );
	void OnButtonDialog( wxCommandEvent& event );
	void OnButtonClear( wxCommandEvent& event );

	void OnPopupButton( wxCommandEvent& event );
	void OnDialogButton( wxCommandEvent& event );
};
