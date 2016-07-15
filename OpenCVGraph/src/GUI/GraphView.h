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
	// Called when the user click on a parameter
	void OnPinLeftMouseDown(GUINodeParam* param, wxPoint pos);
	// Must be called every time the mouse button is released (even if inside a child)
	void OnMouseUp(wxMouseEvent& event);
	// Public because the nodes can send event to it if the mouse is over a node and we still need to handle the event
	// e.g. wiring event
	void OnMouseMotion(wxMouseEvent&);

	// Are we wiring a pin to another at the moment ?
	bool isWiring();
	// Return the pin we selected when we began to wire a pin to another
	GUINodeParam* GetSelectedPin();
	// Add a wire between to pins
	// Called from a GUINodeParam when it accepts a connection with another pin
	void AddWire(GUINodeParam* first, GUINodeParam* second);

protected:
	void Init();
	void ContinuousRefresh(bool);
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);
	void OnTimer(wxTimerEvent&);

	std::vector<GUINode*> m_selectedNodes;

	wxPoint m_mouseWiringStartingPoint;
	// Selected pin when we first left clicked on a pin and began dragging
	GUINodeParam* m_selectedPin = nullptr;
	wxPoint m_mousePosition;
	bool m_mouseWiring = false;

	std::vector<std::pair<GUINodeParam*, GUINodeParam*>> m_wires;
	wxTimer m_timer;

private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif