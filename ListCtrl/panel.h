#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/listctrl.h>

/*
WindowsではwxListCtrlが仮想リスト出は無い場合、
0列目ではiamgeIDを-1にしても0のアイコンが表示された。バグでは？
*/

namespace
{
	wxBitmap icon1;
	wxBitmap icon2;
	wxBitmap icon3;
	wxImageList* imageList = nullptr;
}

void InitIcon()
{
	wxRect rect( 0, 0, 20, 20 );
	wxImage image( rect.GetSize() );
	image.SetRGB( rect, 255, 0, 0 );
	icon1 = image;
	image.SetRGB( rect, 0, 255, 0 );
	icon2 = image;
	image.SetRGB( rect, 0, 0, 255 );
	icon3 = image;

	if (nullptr != imageList)
		delete imageList;
	imageList = new wxImageList( rect.width, rect.height );
	imageList->Add( icon1 );
	imageList->Add( icon2 );
	imageList->Add( icon3 );
}

class myPanel1 : public wxPanel
{
public:
	myPanel1( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		auto list = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL );
		list->SetImageList( imageList , wxIMAGE_LIST_SMALL ); //wxIMAGE_LIST_NORMALでは表示されず

		int idx = 0;
		wxListItem itemCol;
		itemCol.SetText( "Col1" );
		itemCol.SetImage( -1 );
		list->InsertColumn( idx++, itemCol );
		itemCol.SetText( "Col2" );
		list->InsertColumn( idx++, itemCol );
		itemCol.SetText( "Col3" );
		list->InsertColumn( idx++, itemCol );

		for (int row = 0; row < 5; row++)
		{
			list->InsertItem( row, "item" );
			for (int col = 0; col < 3; col++)
			{
				list->SetItem( row, col, wxString::Format( "%d %d", row, col ), (row+col) % 4 -1 );
			}
		}

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( list, 1, wxEXPAND );
		}
		SetSizer( sizer );
	}
};

class myListCtrl : public wxListCtrl
{
public:
	myListCtrl( wxWindow* parent )
		:wxListCtrl( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_VIRTUAL )
	{
		SetImageList( imageList, wxIMAGE_LIST_SMALL ); //wxIMAGE_LIST_NORMALでは表示されず
	}

private:
	wxString OnGetItemText( long item, long column ) const override
	{
		return wxString::Format( "%d, %d", item, column );
	}

	int OnGetItemColumnImage( long item, long column ) const override
	{
		return (item + column) % 4 - 1;
	}
};

class myPanel2 : public wxPanel
{
public:
	myPanel2( wxWindow* parent )
		:wxPanel( parent, wxID_ANY )
	{
		auto list = new myListCtrl( this );

		list->AppendColumn( "Col1" );
		list->AppendColumn( "Col2" );
		list->AppendColumn( "Col3" );

		list->SetItemCount( 5 );

		auto sizer = new wxBoxSizer( wxVERTICAL );
		{
			sizer->Add( list, 1, wxEXPAND );
		}
		SetSizer( sizer );
	}

private:


};