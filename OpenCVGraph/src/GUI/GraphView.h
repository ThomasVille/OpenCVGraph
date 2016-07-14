#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

/* Color of the wire defined by the output parameter type */

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

	// Can be called when clicked in the graphview or in children like GUINodes
	void OnLeftMouseDown(wxMouseEvent& event);

	void OnNodeMouseDown(GUINode* node, wxPoint pos);
	void OnNodeMouseUp(GUINode* node, wxPoint pos);

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