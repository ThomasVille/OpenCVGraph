/////////////////////////////////////////////////////////////////////////////
// Name:        OpenCVGraph.cpp
// Purpose:     Allow developpers to create computer vision algorithms with a node-based interface.
// Author:      Thomas Ville
// Modified by:
// Created:     10/07/2016 (DD/MM/YYYY)
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "GUI/MainFrame.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "wx/wx.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;

private:
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);



// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	// create the main application window
	MyFrame *frame = new MyFrame(wxT("OpenCVGraph v0.0.0.0.0.0.1"),
		wxPoint(50, 50), wxSize(600, 340));

	// and show it (the frames, unlike simple controls, are not shown when
	// created initially)
	frame->Show(true);

	return true;
}