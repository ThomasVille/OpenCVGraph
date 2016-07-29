#ifndef _GUI_GRAPHVIEW_H_
#define _GUI_GRAPHVIEW_H_

/* Color of the wire defined by the output parameter type */
/* Events must be handled at the innermost level of hierarchy
e.g. when the mouse is released on a pin, it's the GUINodeParam parent which should do the job
(check if the types are compatible, ...) and tell the GraphView to do something if needed */
#include <memory>
#include <wx/wx.h>
#include "GUINode.h"
#include "../GraphEngine.h"
class PreviewPanel;
class GraphView : public wxScrolledWindow
{
public:
	GraphView() : wxScrolledWindow(), m_graphEngine(this) { Init(); }
	GraphView(wxWindow *parent,
		wxWindowID winid,
		PreviewPanel* previewPanel,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0) :
		wxScrolledWindow(parent, winid, pos, size, style),
		m_graphEngine(this),
		m_previewPanel(previewPanel)
	{
		Init();
	}

	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnRightMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent&);

	// Redraw asap the whole graph
	void Redraw();

	// Are we wiring a pin to another at the moment ?
	bool isWiring();

	// Return the pin we selected when we began to wire a pin to another
	std::shared_ptr<GUINodeParam> GetSelectedPin();

	// Add a wire between to pins
	// Called from a GUINodeParam when it accepts a connection with another pin
	void AddWire(std::shared_ptr<GUINodeParam> first, std::shared_ptr<GUINodeParam> second);
	void SetLinkState(LinkState state);

	// Set the selected node
	void SetSelected(std::shared_ptr<GUINode> node);
	// Deselect any node previously selected
	void DeselectNode();
	/** Set the selected node to be the entry point of the graph.
	* Call UpdateRealtime and Redraw
	* \sa UpdateRealtime, Redraw
	*/
	void MakeSelectedNodeEntryPoint();

	void AddNode(std::shared_ptr<Node> node);
	std::shared_ptr<Node> GetSelectedNode();
	// Delete the node
	void DeleteNode(std::shared_ptr<GUINode> node);
	// Delete all the wires connected to this pin and its links
	void DeleteWiresConnectedTo(std::shared_ptr<GUINodeParam> pin);

	GraphEngine* GetGraphEngine();

	void RunOneShot();
	void RunRealtime();
	void SimulationError(std::string msg);

	std::shared_ptr<Node> GetEntryPoint();
protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);
	// Proceed to a new RunOneShot if we are in realtime mode
	void UpdateRealtime();
	// Change the entry point. No check.
	void SetEntryPoint(std::shared_ptr<Node> node);

	// List of all the children GUINodes
	std::vector<std::shared_ptr<GUINode>> m_GUINodes;

	wxPoint m_mouseWiringStartingPoint;
	// Selected pin when we first left clicked on a pin and began dragging
	std::shared_ptr<GUINodeParam> m_selectedPin;
	std::shared_ptr<GUINode> m_selectedNode;
	wxPoint m_mousePosition;
	bool m_mouseWiring = false;
	LinkState m_linkState = END_MISSING; // State of the link we are currently dragging with the mouse
	// Dragging stuff
	bool m_isDragging = false;


	std::vector<std::pair<std::shared_ptr<GUINodeParam>, std::shared_ptr<GUINodeParam>>> m_wires;

	GraphEngine m_graphEngine;
	bool m_realtimeStarted = false;
	std::string m_simulationStatus;
	std::shared_ptr<Node> m_entryPoint;

	PreviewPanel* m_previewPanel;

	wxSize m_canvasSize;
private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif