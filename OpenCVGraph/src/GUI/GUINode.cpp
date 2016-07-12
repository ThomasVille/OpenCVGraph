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
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);;

	if (gc)
	{
		gc->SetBrush(*wxRED_BRUSH);
		gc->SetPen(wxPen(*wxBLACK, 1));
		gc->DrawRoundedRectangle(0, 0, GetSize().GetWidth()-1, GetSize().GetHeight()-1, 10);
		delete gc;
	}

	
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