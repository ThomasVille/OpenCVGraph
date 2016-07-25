#include "GraphView.h"
#include <wx/dcbuffer.h>
#include "MainFrame.h"
using namespace std;
wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::OnPinLeftMouseDown(GUINodeParam* param, wxPoint pos)
{
	m_mouseWiringStartingPoint = pos;
	m_selectedPin = param;
	m_mouseWiring = true;
	m_linkState = END_MISSING;
	//ContinuousRefresh(true);
}
void GraphView::OnMouseUp(wxMouseEvent& event)
{
	m_mouseWiring = false;
	m_selectedPin = nullptr;
	Redraw();
}

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
	Bind(wxEVT_MOTION, &GraphView::OnMouseMotion, this);
	Bind(wxEVT_LEFT_UP, &GraphView::OnMouseUp, this);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	// Initialize the graph engine
}

wxSize GraphView::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GraphView::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

	if (gc)
	{
		// Draw the background
		wxDouble width, height;
		gc->GetSize(&width, &height);
		gc->SetPen(*wxWHITE_PEN);
		gc->SetBrush(*wxWHITE_BRUSH);
		gc->DrawRectangle(0, 0, width, height);
		// Display the simulation status
		gc->SetFont(font, *wxBLACK);
		gc->DrawText(m_simulationStatus, 0, 0);
		// Draw the link when we draw a link with the mouse
		if (m_mouseWiring) {
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			switch (m_linkState) { // Change the color of the link depending on its state
			case ERROR_SAME_WAY:
				gc->SetPen(wxPen(*wxRED, 1));
				break;
			case LINK_OK:
				gc->SetPen(wxPen(*wxGREEN, 1));
				break;
			case END_MISSING:
				gc->SetPen(wxPen(*wxBLACK, 1));
				break;
			}

			wxGraphicsPath path = gc->CreatePath();
			path.MoveToPoint(m_mousePosition);
			path.AddLineToPoint(m_mouseWiringStartingPoint);
			gc->DrawPath(path);
		}
		// Draw the wires
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
		gc->SetPen(wxPen(*wxBLACK, 2));
		wxGraphicsPath path = gc->CreatePath();
		for (auto wire : m_wires) {
			path.MoveToPoint(wire.first->GetPinPosition());
			int distance = abs(wire.first->GetPinPosition().x - wire.second->GetPinPosition().x);
			path.AddCurveToPoint(wire.first->GetPinPosition()+wxPoint(distance/2,0), wire.second->GetPinPosition()-wxPoint(distance/2,0), wire.second->GetPinPosition());
		}
		gc->DrawPath(path);
		// Draw something to distinguish the selected node from the others
		if (m_selectedNode != nullptr) {
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(*wxBLACK, 4));
			gc->DrawRectangle(m_selectedNode->GetPosition().x,
				m_selectedNode->GetPosition().y,
				m_selectedNode->GetSize().GetWidth(),
				m_selectedNode->GetSize().GetHeight());
		}
		
		delete gc;
	}
	// Reset the link's state
	// Needed because GUINodeParams can't reset the link to END_MISSING when the mouse goes outside of them
	m_linkState = END_MISSING;

	event.Skip();
}

void GraphView::UpdateRealtime()
{
	if (m_realtimeStarted)
		m_graphEngine.RunOneShot(m_entryPoint);
}

void GraphView::OnMouseMotion(wxMouseEvent &event)
{
	m_mousePosition = event.GetPosition();
	
	// Redraw the graph only if we are dragging a link
	if(isWiring())
		Redraw();
}

bool GraphView::isWiring()
{
	return m_selectedPin != nullptr ? true : false;
}

GUINodeParam * GraphView::GetSelectedPin()
{
	return m_selectedPin;
}

void GraphView::AddWire(GUINodeParam * first, GUINodeParam * second)
{
	if (first->GetParameter()->GetParamType() == INPUT_PARAM) {
		// Add the graphical wire
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(second, first));
		// Add the link between the two nodes
		second->GetParameter()->AddLink(first->GetParameter());
		first->GetParameter()->AddLink(second->GetParameter());
	}
	if (first->GetParameter()->GetParamType() == OUTPUT_PARAM) {
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(first, second));
		// Add the link between the two nodes
		first->GetParameter()->AddLink(second->GetParameter());
		second->GetParameter()->AddLink(first->GetParameter());
	}
	UpdateRealtime();
}

void GraphView::SetLinkState(LinkState state)
{
	m_linkState = state;
}

void GraphView::SetSelected(GUINode * node)
{
	m_selectedNode = node;
}

void GraphView::AddNode(shared_ptr<Node> node)
{
	m_graphEngine.AddNode(node);
	m_GUINodes.push_back(new GUINode(this, node));
	// Let's make the last added node the entry point for the moment
	m_entryPoint = node.get();
	UpdateRealtime();
}

void GraphView::DeleteNode(Node * node)
{
	// Delete all the wires related to this node
	for (int i = 0; i < m_wires.size(); i++) {
		// If either end of the wire is the node we are deleting
		if (((GUINode*)m_wires[i].first->GetParent())->GetNode().get() == node ||
			((GUINode*)m_wires[i].second->GetParent())->GetNode().get() == node) {
			m_wires.erase(m_wires.begin()+i); // delete the link
			i--;
			continue;
		}
	}
	// Delete the associated GUINode
	for(int i = 0; i < m_GUINodes.size(); i++)
		if (m_GUINodes[i]->GetNode().get() == node) {
			m_GUINodes.erase(m_GUINodes.begin() + i);
			break;
		}
	// Delete the node in the graph engine
	m_graphEngine.DeleteNode(node);
	// Check if it's the entry point, in this case, reset the entry point
	if (m_entryPoint == node)
		m_entryPoint = nullptr;
	// Check if it's selected
	if (node == m_selectedNode->GetNode().get())
		m_selectedNode = nullptr;
	UpdateRealtime();
	Refresh();
}

void GraphView::DeleteWiresConnectedTo(GUINodeParam * pin)
{
	// Delete the links
	pin->GetParameter()->RemoveAllLinks();
	// Delete the wires
	for (int i = 0; i < m_wires.size(); i++) {
		if (m_wires[i].first == pin || m_wires[i].second == pin) {
			m_wires.erase(m_wires.begin() + i);
			i--;
		}
	}
	UpdateRealtime();
	Refresh();
}

GraphEngine * GraphView::GetGraphEngine()
{
	return &m_graphEngine;
}

void GraphView::RunOneShot()
{
	m_graphEngine.RunOneShot(m_entryPoint);
	Refresh();
}
void GraphView::RunRealtime()
{
	m_realtimeStarted = true;
	m_graphEngine.RunOneShot(m_entryPoint);
	Refresh();
}

void GraphView::SimulationError(std::string msg)
{
	m_simulationStatus = msg;
	//((MyFrame*)m_parent)->SetSimulationStatus(msg);
}

Node * GraphView::GetEntryPoint()
{
	return m_entryPoint;
}

void GraphView::Redraw()
{
	Refresh();
	Update();
}
