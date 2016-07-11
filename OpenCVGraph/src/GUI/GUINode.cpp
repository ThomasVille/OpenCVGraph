#include "GUINode.h"

wxIMPLEMENT_DYNAMIC_CLASS(GUINode, wxControl);

void GUINode::Init()
{
	Bind(wxEVT_LEFT_DOWN, &GUINode::OnLeftMouseDown, this);
	Bind(wxEVT_LEFT_UP, &GUINode::OnLeftMouseUp, this);
	Bind(wxEVT_MOTION, &GUINode::OnMouseMotion, this);
	Bind(wxEVT_PAINT, &GUINode::OnPaint, this);
}

wxSize GUINode::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GUINode::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRoundedRectangle(wxRect(wxPoint(0, 0), GetSize()), 10);
	event.Skip();
}

void GUINode::OnLeftMouseDown(wxMouseEvent& event)
{
	m_isDragging = true;
	m_firstDraggingPoint = event.GetPosition();
}

void GUINode::OnLeftMouseUp(wxMouseEvent& event)
{
	m_isDragging = false;
}

void GUINode::OnMouseMotion(wxMouseEvent& event)
{
	if (m_isDragging && event.LeftIsDown())
		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
}