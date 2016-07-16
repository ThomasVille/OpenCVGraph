#include "GraphView.h"

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
	//ContinuousRefresh(false);
}

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
	Bind(wxEVT_MOTION, &GraphView::OnMouseMotion, this);
	Bind(wxEVT_LEFT_UP, &GraphView::OnMouseUp, this);

}

wxSize GraphView::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GraphView::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);


	if (gc)
	{
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
			//path.AddLineToPoint(wire.second->GetPinPosition());
		}
		gc->DrawPath(path);

		delete gc;
	}
	// Reset the link's state
	// Needed because GUINodeParams can't reset the link to END_MISSING when the mouse goes outside of them
	m_linkState = END_MISSING;

	event.Skip();
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
	if(first->GetParameter().GetParamType() == INPUT_PARAM)
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(second, first));
	if (first->GetParameter().GetParamType() == OUTPUT_PARAM)
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(first, second));
}

void GraphView::SetLinkState(LinkState state)
{
	m_linkState = state;
}

void GraphView::AddNode(shared_ptr<Node> node)
{
	new GUINode(this, node);
}

void GraphView::Redraw()
{
	Refresh();
	Update();
}
