#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

/* Color of the wire defined by the output parameter type */
/* Events must be handled at the innermost level of hierarchy
e.g. when the mouse is released on a pin, it's the GUINodeParam parent which should do the job
(check if the types are compatible, ...) and tell the GraphView to do something if needed */

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

	// Begin the drawing of the wire
	void OnPinLeftMouseDown(GUINode* node, wxPoint pos);
	// Must be called every time the mouse button is released (even if inside a child)
	void OnMouseUp(wxMouseEvent& event);

protected:
	void Init();
	void ContinuousRefresh(bool);
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);
	void OnMouseMotion(wxMouseEvent&);
	void OnTimer(wxTimerEvent&);

	std::vector<GUINode*> m_selectedNodes;

	wxPoint m_mouseWiringStartingPoint;
	wxPoint m_mousePosition;
	bool m_mouseWiring = false;

	wxTimer m_timer;

private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif