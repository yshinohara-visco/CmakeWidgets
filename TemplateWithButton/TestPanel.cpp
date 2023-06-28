#include "TestPanel.h"

TestPanel::TestPanel( wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size, long style, wxString name )
	:wxPanel( parent, id, pos, size, style, name )
{
	SetBackgroundColour( *wxWHITE );
}

TestPanel::~TestPanel()
{

}