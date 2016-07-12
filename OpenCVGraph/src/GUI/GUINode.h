#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Node.h"
class GUINode : public wxControl
{
public:
	GUINode():
		wxControl(),
		m_node(Node({}, {}))
	{ Init(); };
	GUINode(wxWindow *parent, Node node):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxDefaultValidator),
		m_node(node)
	{
		Init();
	}

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

	// Draws the node's body
	void OnPaint(wxPaintEvent&);
	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	// Best size for the node according to its content
	wxSize m_bestSize;
	int m_maxParamsPerColumn;

	// Dragging stuff
	bool m_isDragging = false;
	wxPoint m_firstDraggingPoint;

	// The node to represent
	Node m_node;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINode);
};

#endif