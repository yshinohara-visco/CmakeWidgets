#include "myPanel.h"

class myFrame : public wxFrame
{
public:
	myFrame()
		:wxFrame( NULL, wxID_ANY, "test" )
	{
		SetSize( 640, 480 );
		SetBackgroundColour( wxColor( 230, 240, 255 ) );
		myPanel* pnl = new myPanel( this );
	}

private:

};

class myApp : public wxApp
{
public:
	virtual bool OnInit()
	{
		myFrame* frame = new myFrame();
		frame->Show();
		return true;
	}
};

IMPLEMENT_APP( myApp );