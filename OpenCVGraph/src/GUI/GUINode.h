#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_
#include <memory>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Node.h"
#include "GUINodeParam.h"
#include "Preview\PreviewPanel.h"

class GraphView;
class GUINode
{
public:
	GUINode(GraphView *parent, std::shared_ptr<Node> node):
		m_graphView(parent),
		m_node(node)
	{
		Init();
	}

	inline std::shared_ptr<Node> GetNode() {
		return m_node;
	}
	inline std::vector<std::shared_ptr<GUINodeParam>> GetParams() {
		return m_params;
	}

	void UpdatePreview();

	void Draw(wxGraphicsContext *gc);

	void StartDrag(wxPoint startingPoint);

	void Drag(wxPoint p);

	void SetPosition(wxPoint p);

	wxRect GetRect();

	bool IsInside(wxPoint p);

	void Select();

	void Deselect();

protected:
	void Init();

	//! Rectangle in which the node is drawn (position and size)
	wxRect m_rect;
	//! Offset between the mouse and the node's position when we begin to drag the node
	wxPoint m_offset;
	//! True if the node is selected and we must highlight it
	bool m_isSelected = false;

	//! Best size for the node according to its content
	wxSize m_bestSize;
	//! Maximum number of parameters on one column
	int m_maxParamsPerColumn = 0;

	//! The underlying node
	std::shared_ptr<Node> m_node;
	//! List of graphical parameters
	std::vector<std::shared_ptr<GUINodeParam>> m_params;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
};

#endif