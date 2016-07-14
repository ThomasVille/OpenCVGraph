#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::OnPinLeftMouseDown(GUINode* node, wxPoint pos)
{
	m_mouseWiringStartingPoint = pos;
	m_mouseWiring = true;
	ContinuousRefresh(true);
}
void GraphView::OnMouseUp(GUINode* node, wxPoint pos)
{
	m_mouseWiring = false;
	ContinuousRefresh(false);
}

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));
	new GUINode(this, Node({ InputParam("a"), InputParam("b") }, { OutputParam("y") }));
	new GUINode(this, Node({ InputParam("x"), InputParam("y") }, { OutputParam("z") }));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
	Bind(wxEVT_MOTION, &GraphView::OnMouseMotion, this);

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
	dc.SetBrush(*wxWHITE_BRUSH);
	//(GUINode*)(event.GetPropagatedFrom())->;
	for (int i = 0; i < m_children.size(); i++) {
		//if()
	}
	dc.SetBrush(*wxBLACK_BRUSH);
	if (m_mouseWiring) {
		dc.DrawLine(m_mousePosition, m_mouseWiringStartingPoint);
	}
	event.Skip();
}

void GraphView::OnMouseMotion(wxMouseEvent &event)
{
	m_mousePosition = event.GetPosition();
}

void GraphView::OnTimer(wxTimerEvent &event)
{
	Refresh();
}
