#ifndef _GUI_GUINODEPARAM_H_
#define _GUI_GUINODEPARAM_H_
#include <memory>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Parameter.h"

class GraphView;
class GUINode;
enum LinkState { ERROR_SAME_WAY, LINK_OK, END_MISSING };
class GUINodeParam
{
public:
	GUINodeParam(GUINode* parent, GraphView* graphView, std::shared_ptr<Parameter> param, wxRect rect):
		m_parent(parent),
		m_graphView(graphView),
		m_parameter(param),
		m_rect(rect)
	{
		Init();
	}

	void Draw(wxGraphicsContext* gc);

	void Move(wxPoint offset);

	// Return the position of the pin in *GraphView* coordinates
	wxPoint GetPinPosition();

	std::shared_ptr<Parameter> GetParameter();

	GUINode* GetParent();

	// Return true if the point is inside this object
	bool IsInside(wxPoint p);

protected:
	void Init();

	/*void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	void OnPinRightMouseUp(wxMouseEvent& event);
	void OnPinLeftMouseDown(wxMouseEvent&);
	void OnPinLeftMouseUp(wxMouseEvent&);
	void OnPinMouseMotion(wxMouseEvent& event);

	void OnNameLeftMouseDown(wxMouseEvent&);
	void OnNameLeftMouseUp(wxMouseEvent&);
	void OnNameMouseMotion(wxMouseEvent& event);*/

	wxRect m_rect; // Rect of this widget
	GUINode *m_parent;

	std::shared_ptr<Parameter> m_parameter;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
};

#endif