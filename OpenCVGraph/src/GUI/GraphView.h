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

class GraphView : public wxScrolledWindow
{
public:
	GraphView() : wxScrolledWindow(), m_graphEngine(this) { Init(); }
	GraphView(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0) :
		wxScrolledWindow(parent, winid, pos, size, style),
		m_graphEngine(this)
	{
		Init();
	}

	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);

	// Begin the drawing of the wire
	// Called when the user click on a parameter
	void OnPinLeftMouseDown(GUINodeParam* param, wxPoint pos);
	// Must be called every time the mouse button is released (even if inside a child)
	void OnMouseUp(wxMouseEvent& event);
	// Public because the nodes can send event to it if the mouse is over a node and we still need to handle the event
	// e.g. wiring event
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
	void SetSelected(GUINode* node);

	void AddNode(std::shared_ptr<Node> node);
	// Delete the node at this address
	// Called by a node when right clicked
	void DeleteNode(Node* node);
	// Delete all the wires connected to this pin and its links
	void DeleteWiresConnectedTo(GUINodeParam* pin);

	GraphEngine* GetGraphEngine();

	void RunOneShot();
	void RunRealtime();
	void SimulationError(std::string msg);

	Node* GetEntryPoint();
protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);
	// Proceed to a new RunOneShot if we are in realtime mode
	void UpdateRealtime();
	// List of all the children GUINodes
	std::vector<GUINode*> m_GUINodes;

	wxPoint m_mouseWiringStartingPoint;
	// Selected pin when we first left clicked on a pin and began dragging
	std::shared_ptr<GUINodeParam> m_selectedPin;
	GUINode* m_selectedNode = nullptr;
	wxPoint m_mousePosition;
	bool m_mouseWiring = false;
	LinkState m_linkState = END_MISSING; // State of the link we are currently dragging with the mouse
	// Dragging stuff
	bool m_isDragging = false;


	std::vector<std::pair<std::shared_ptr<GUINodeParam>, std::shared_ptr<GUINodeParam>>> m_wires;

	GraphEngine m_graphEngine;
	bool m_realtimeStarted = false;
	std::string m_simulationStatus;
	Node* m_entryPoint = nullptr;
private:
	wxDECLARE_DYNAMIC_CLASS(GraphView);
};

#endif