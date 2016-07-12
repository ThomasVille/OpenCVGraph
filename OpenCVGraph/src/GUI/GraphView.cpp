#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::Init()
{
	SetVirtualSize(wxSize(1920, 1080));
	new GUINode(this, wxID_ANY, wxPoint(50, 50), wxSize(100, 100));
	new GUINode(this, wxID_ANY, wxPoint(200,200), wxSize(100,100));

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