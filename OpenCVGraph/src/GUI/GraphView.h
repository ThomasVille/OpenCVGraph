#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

#include <wx/wx.h>
#include "GUINode.h"

class GraphView : public wxControl
{
public:
	GraphView() : wxControl() { Init(); }
	GraphView(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& val = wxDefaultValidator) :
		wxControl(parent, winid, pos, size, style, val)
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