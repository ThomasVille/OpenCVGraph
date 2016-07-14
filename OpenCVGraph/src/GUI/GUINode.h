#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Node.h"
#include "GUINodeParam.h"

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

	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	void OnPinMouseDown(wxMouseEvent&);
	void OnPinMouseUp(wxMouseEvent&);
	void OnPinMouseMotion(wxMouseEvent&);
protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

	// Draws the node's body
	void OnPaint(wxPaintEvent&);


	

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