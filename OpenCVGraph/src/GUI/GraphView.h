#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

#include <wx/wx.h>
#include "GUINode.h"

class GraphView : public wxScrolledWindow
{
public:
	GraphView() : wxScrolledWindow() { Init(); }
	GraphView(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0) :
		wxScrolledWindow(parent, winid, pos, size, style)
	{
		Init();
	}

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);

private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif