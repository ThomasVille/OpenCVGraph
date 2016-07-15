#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::OnPinLeftMouseDown(GUINodeParam* param, wxPoint pos)
{
	m_mouseWiringStartingPoint = pos;
	m_selectedPin = param;
	m_mouseWiring = true;
	ContinuousRefresh(true);
}
void GraphView::OnMouseUp(wxMouseEvent& event)
{
	m_mouseWiring = false;
	m_selectedPin = nullptr;
	ContinuousRefresh(false);
}

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));
	new GUINode(this, Node({ Parameter("a", INPUT_PARAM), Parameter("b", INPUT_PARAM) }, { Parameter("y", OUTPUT_PARAM) }));
	new GUINode(this, Node({ Parameter("x", INPUT_PARAM), Parameter("y", INPUT_PARAM) }, { Parameter("z", OUTPUT_PARAM) }));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
	Bind(wxEVT_MOTION, &GraphView::OnMouseMotion, this);
	Bind(wxEVT_LEFT_UP, &GraphView::OnMouseUp, this);

	m_timer.SetOwner(this);
	Bind(wxEVT_TIMER, &GraphView::OnTimer, this);
}

void GraphView::ContinuousRefresh(bool continuous)
{
	if (continuous)
		m_timer.Start(1);
	else
		m_timer.Stop();
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
		gc->SetBrush(*wxWHITE_BRUSH);
		//(GUINode*)(event.GetPropagatedFrom())->;
		for (int i = 0; i < m_children.size(); i++) {
			//if()
		}
		gc->SetBrush(*wxBLACK_BRUSH);
		gc->SetPen(wxPen(*wxBLACK, 1));
		if (m_mouseWiring) {
			wxGraphicsPath path = gc->CreatePath();
			path.MoveToPoint(m_mousePosition);
			path.AddLineToPoint(m_mouseWiringStartingPoint);
			gc->DrawPath(path);
		}
		// Draw the wires
		gc->SetPen(wxPen(*wxBLACK, 2));
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
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

	event.Skip();
}

void GraphView::OnMouseMotion(wxMouseEvent &event)
{
	m_mousePosition = event.GetPosition();
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
	if(first->GetParameter().GetType() == INPUT_PARAM)
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(second, first));
	if (first->GetParameter().GetType() == OUTPUT_PARAM)
		m_wires.push_back(std::pair<GUINodeParam*, GUINodeParam*>(first, second));
}

void GraphView::OnTimer(wxTimerEvent &event)
{
	Refresh();
}
