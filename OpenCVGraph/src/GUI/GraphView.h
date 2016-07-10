#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

#include <wx/wx.h>

class GraphView : public wxWindow
{
public:
	GraphView() : wxWindow() { Init(); }
	GraphView(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& val = wxDefaultValidator,
		const wxString& name = "GraphView") :
		wxWindow(parent, winid, pos, size, style, name)
	{
		Init();
	}

	// accessors...
protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);
private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif