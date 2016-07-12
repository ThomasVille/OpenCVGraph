#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));
	new GUINode(this, Node({ InputParam("a"), InputParam("b") }, { OutputParam("y") }));
	new GUINode(this, Node({ InputParam("x"), InputParam("y") }, { OutputParam("z") }));

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
}

wxSize GraphView::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GraphView::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.SetBrush(*wxWHITE_BRUSH);
	//dc.DrawRectangle(wxRect(wxPoint(0, 0), GetSize()));
	event.Skip();
}