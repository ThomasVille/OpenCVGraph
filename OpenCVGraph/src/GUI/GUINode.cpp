#include "GUINode.h"

wxIMPLEMENT_DYNAMIC_CLASS(GUINode, wxControl);

void GUINode::Init()
{

	Bind(wxEVT_PAINT, &GUINode::OnPaint, this);
}

wxSize GUINode::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GUINode::OnPaint(wxPaintEvent &)
{
	wxPaintDC dc(this);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRoundedRectangle(wxRect(wxPoint(10, 10), wxPoint(100, 100)), 10);
}
