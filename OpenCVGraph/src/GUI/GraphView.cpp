#include "GraphView.h"

wxIMPLEMENT_DYNAMIC_CLASS(GraphView, wxControl);

void GraphView::Init()
{
	new GUINode(this, wxID_ANY);

	Bind(wxEVT_PAINT, &GraphView::OnPaint, this);
}

wxSize GraphView::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void GraphView::OnPaint(wxPaintEvent &)
{

}
