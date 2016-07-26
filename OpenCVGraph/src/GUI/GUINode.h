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


	void OnRightMouseUp(wxMouseEvent& event);
protected:
	void Init();

	PreviewPanel* m_preview;

	wxRect m_rect;
	wxPoint m_offset;

	// Best size for the node according to its content
	wxSize m_bestSize;
	int m_maxParamsPerColumn;

	// The node to represent
	std::shared_ptr<Node> m_node;

	std::vector<std::shared_ptr<GUINodeParam>> m_params;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
};

#endif