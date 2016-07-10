#ifndef _GUI_MAINFRAME_H_
#define _GUI_MAINFRAME_H_

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>
#include "GraphView.h"

class MyFrame : public wxFrame
{
public:
	// ctor(s)
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MyFrame();

	// GUI Building
	void CreateToolbar();
	void CreateStatus();
	void CreateMenuBar();
	void CreateGraphNotebook();
	void CreatePanes();

	// Events callbacks
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	wxAuiManager m_mgr;
	wxAuiToolBar* m_mainToolbar;
	wxAuiNotebook *m_graphNotebook;

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