#include "GraphView.h"
#include <wx/dcbuffer.h>
#include "MainFrame.h"
#include "Resources.h"
using namespace std;
wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::OnLeftMouseDown(wxMouseEvent& event)
{
	// Remove previously selected node
	SetSelected(nullptr);
	// Check if we are inside a node and select it
	for(auto node : m_GUINodes)
		if (node->IsInside(event.GetPosition())) {
			SetSelected(node);
			// Check if we are clicking on a pin
			bool inPin = false;
			for(auto& p : node->GetParams())
				if (p->IsInsidePin(event.GetPosition())) {
					m_mouseWiringStartingPoint = p->GetPinPosition();
					m_selectedPin = p;
					m_mouseWiring = true;
					m_linkState = END_MISSING;
					inPin = true;
				}
			// If we are not in a pin, drag the node
			if (!inPin) {
				m_isDragging = true;
				node->StartDrag(event.GetPosition());
			}
			break;
		}
}

void GraphView::OnLeftMouseUp(wxMouseEvent& event)
{
	m_isDragging = false;
	m_mouseWiring = false;

	// Check if we are inside a pin
	if (isWiring()) {
		for (auto node : m_GUINodes)
			if (node->IsInside(event.GetPosition())) {
				for (auto& p : node->GetParams())
					if (p->IsInsidePin(event.GetPosition())) {
						if(p->GetParameter()->IsCompatible(GetSelectedPin()->GetParameter()))
							AddWire(p, GetSelectedPin());

						Redraw();
						return;
					}
			}
	}
	

	
}

void GraphView::OnMouseMotion(wxMouseEvent& event)
{
	// If we are dragging a node around
	if (m_isDragging && event.LeftIsDown()) {
		m_selectedNode->Drag(event.GetPosition());
		Redraw();
	}
	else
	{
		m_mousePosition = event.GetPosition();
		// Redraw the graph only if we are dragging a link
		if (isWiring())
			Redraw();
	}
}

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
	Bind(wxEVT_MOTION, &GraphView::OnMouseMotion, this);
	Bind(wxEVT_LEFT_UP, &GraphView::OnLeftMouseUp, this);
	Bind(wxEVT_LEFT_DOWN, &GraphView::OnLeftMouseDown, this);
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
		// Draw the nodes
		for (auto node : m_GUINodes)
			node->Draw(gc);
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
			gc->SetPen(wxPen(RES_NODE_HIGHLIGHT, 1));
			gc->DrawRectangle(m_selectedNode->GetRect().x-1,
				m_selectedNode->GetRect().y-1,
				m_selectedNode->GetRect().GetWidth()+1,
				m_selectedNode->GetRect().GetHeight()+1);
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

bool GraphView::isWiring()
{
	return m_selectedPin != nullptr ? true : false;
}

std::shared_ptr<GUINodeParam> GraphView::GetSelectedPin()
{
	return m_selectedPin;
}

void GraphView::AddWire(shared_ptr<GUINodeParam> first, shared_ptr<GUINodeParam> second)
{
	if (first->GetParameter()->GetParamType() == INPUT_PARAM) {
		// Add the graphical wire
		m_wires.push_back(std::pair<shared_ptr<GUINodeParam>, shared_ptr<GUINodeParam>>(second, first));
		// Add the link between the two nodes
		second->GetParameter()->AddLink(first->GetParameter());
		first->GetParameter()->AddLink(second->GetParameter());
	}
	if (first->GetParameter()->GetParamType() == OUTPUT_PARAM) {
		m_wires.push_back(std::pair<shared_ptr<GUINodeParam>, shared_ptr<GUINodeParam>>(first, second));
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
	Redraw();
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
		if (m_wires[i].first.get() == pin || m_wires[i].second.get() == pin) {
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
