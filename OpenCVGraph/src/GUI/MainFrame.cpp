#include "MainFrame.h"

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	SetIcon(wxICON(sample));

	// create a menu bar
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(Event_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(Event_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile, wxT("&File"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
	CreateStatusBar(4);
	SetStatusText(wxT("Welcome to OpenCVGraph"));
	SetStatusText(wxT("Correct graph"), Status_Correct);
	SetStatusText(wxT("Inputs : 0"), Status_Inputs);
	SetStatusText(wxT("Outputs : 0"), Status_Outputs);
#endif // wxUSE_STATUSBAR

	Bind(wxEVT_MENU, &MyFrame::OnQuit, this, Event_Quit);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, Event_About);
}

MyFrame::~MyFrame()
{
}

// ----------------------------------------------------------------------------
// standard event handlers
// ----------------------------------------------------------------------------

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("Building computer vision algorithms visually.\n"
		"Copyright (c) 2016 Thomas Ville",
		"About OpenCVGraph",
		wxOK | wxICON_INFORMATION, this);
}
