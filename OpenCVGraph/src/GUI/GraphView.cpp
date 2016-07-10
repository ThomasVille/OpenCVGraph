#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxWindow);

void GraphView::Init()
{
}

wxSize GraphView::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GraphView::OnPaint(wxPaintEvent &)
{
	wxPaintDC dc(this);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRoundedRectangle(wxRect(wxPoint(10, 10), wxPoint(100, 100)), 10);
}
