#ifndef _GUI_MAINFRAME_H_
#define _GUI_MAINFRAME_H_

#include <wx/wx.h>

// IDs for the controls and the menu commands
enum
{
	// menu items
	Event_Quit = 1,
	Event_About
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
	// ctor(s)
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MyFrame();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	// symbolic names for the status bar fields
	enum
	{
		Status_Main = 0,
		Status_Correct,
		Status_Inputs,
		Status_Outputs
	};

};

#endif