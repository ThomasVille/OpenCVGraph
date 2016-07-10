#include "MainFrame.h"

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE)
{
	// tell wxAuiManager to manage this frame
	m_mgr.SetManagedWindow(this);

	m_notebookStyle = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
	m_notebookTheme = 0;

	SetIcon(wxICON(sample));

	// create a menu bar
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(MENU_ABOUT, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(MENU_QUIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile, wxT("&File"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
	
	// Create the statusbar
	CreateStatusBar(4);
	SetStatusText(wxT("Welcome to OpenCVGraph"));
	SetStatusText(wxT("Correct graph"), SB_CORRECT);
	SetStatusText(wxT("Inputs : 0"), SB_INPUTS);
	SetStatusText(wxT("Outputs : 0"), SB_OUTPUTS);

	// Create the toolbar
	wxAuiToolBar* tb1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE);

	tb1->SetToolBitmapSize(wxSize(16, 16));
	tb1->AddTool(TB_NEW_FILE, wxT("New file"), wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(16, 16)));
	tb1->AddSeparator();
	tb1->AddTool(TB_OPEN_FILE, wxT("Open file"), wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(16, 16)));
	tb1->Realize();
	
	//// Create the panes
	// Toolbar pane
	m_mgr.AddPane(tb1, wxAuiPaneInfo().
		Name(wxT("tb1")).Caption(wxT("Big Toolbar")).
		ToolbarPane().Top());

	m_mgr.AddPane(new wxTextCtrl(this, wxID_ANY, "Here goes the file explorer", wxPoint(0, 0), wxSize(200, 90), wxNO_BORDER | wxTE_MULTILINE),
		wxAuiPaneInfo().Name(wxT("file_explorer")).Caption(wxT("File explorer")).
		Left().Row(0).Position(0).Hide());
	m_mgr.AddPane(new wxTextCtrl(this, wxID_ANY, "Here goes all the available nodes", wxPoint(0, 0), wxSize(200, 90), wxNO_BORDER | wxTE_MULTILINE),
		wxAuiPaneInfo().Name(wxT("available_nodes")).Caption(wxT("Available nodes")).
		Left().Row(1).Position(0));

	m_mgr.AddPane(new wxTextCtrl(this, wxID_ANY, "Here goes the nodes properties", wxPoint(0, 0), wxSize(200, 90), wxNO_BORDER | wxTE_MULTILINE),
		wxAuiPaneInfo().Name(wxT("node_properties")).Caption(wxT("Node properties")).
		Right().Row(0).Position(0));

	m_mgr.AddPane(new wxTextCtrl(this, wxID_ANY, "Here goes the preview images", wxPoint(0, 0), wxSize(90, 200), wxNO_BORDER | wxTE_MULTILINE),
		wxAuiPaneInfo().Name(wxT("preview_images")).Caption(wxT("Preview")).
		Bottom().Row(0).Position(0));

	m_mgr.AddPane(new wxTextCtrl(this, wxID_ANY, "Here goes the main tabs", wxPoint(0, 0), wxSize(300, 180), wxNO_BORDER | wxTE_MULTILINE),
		wxAuiPaneInfo().Name(wxT("graph_notebook")).Caption(wxT("Graph notebook")).
		Center().CaptionVisible(false));


	// Allows to resize panes with real-time preview
	m_mgr.SetFlags(m_mgr.GetFlags() ^ wxAUI_MGR_LIVE_RESIZE);

	// "commit" all changes made to wxAuiManager
	m_mgr.Update();

	// Bind the events
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, MENU_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnQuit, this, MENU_QUIT);
}

MyFrame::~MyFrame()
{
	m_mgr.UnInit();
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
