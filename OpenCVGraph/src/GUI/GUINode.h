#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_
#include <memory>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Node.h"
#include "GUINodeParam.h"
#include "Preview\PreviewPanel.h"

class GraphView;
class GUINode : public wxControl
{
public:
	GUINode():
		wxControl(),
		m_node(std::make_shared<Node>())
	{ Init(); };
	GUINode(wxWindow *parent, std::shared_ptr<Node> node):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxDefaultValidator),
		m_node(node)
	{
		Init();
	}

	inline std::shared_ptr<Node> GetNode() {
		return m_node;
	}

	void UpdatePreview();

	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	void OnPinLeftMouseUp(wxMouseEvent&);
	void OnPinMouseMotion(wxMouseEvent&);
protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

	PreviewPanel* m_preview;

	// Draws the node's body
	void OnPaint(wxPaintEvent&);

	// Best size for the node according to its content
	wxSize m_bestSize;
	int m_maxParamsPerColumn;

	// Dragging stuff
	bool m_isDragging = false;
	wxPoint m_firstDraggingPoint;

	// The node to represent
	std::shared_ptr<Node> m_node;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINode);
};

#endif