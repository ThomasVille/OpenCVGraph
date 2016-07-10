#ifndef _GUI_MAINFRAME_H_
#define _GUI_MAINFRAME_H_

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>

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
	wxAuiManager m_mgr;

	// Default style & theme for the notebooks
	long m_notebookStyle;
	long m_notebookTheme;

	enum
	{
		// status bar fields
		SB_MAIN = 0,
		SB_CORRECT,
		SB_INPUTS,
		SB_OUTPUTS,

		// menu items
		MENU_QUIT = 1,
		MENU_ABOUT,

		// toolbar
		TB_NEW_FILE,
		TB_OPEN_FILE
	};

};

#endif