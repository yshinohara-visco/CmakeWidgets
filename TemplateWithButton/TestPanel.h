#include <wx/wx.h>

class TestPanel : public wxPanel
{
public:
	TestPanel( wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, long style = wxTAB_TRAVERSAL, wxString name = "" );
	~TestPanel();

private:
};