#include "GUINode.h"
#include "GraphView.h"
wxIMPLEMENT_DYNAMIC_CLASS(GUINode, wxControl);

void GUINode::Init()
{
	m_graphView = (GraphView*)m_parent;

	// Compute the best width
	m_bestSize.SetWidth(200); // Must be computed depending on the lengths of the inputs and outputs parameters
	// Compute the best height
	int nbInputs = m_node.GetInputs().size();
	int nbOutputs = m_node.GetOutputs().size();
	m_maxParamsPerColumn = nbInputs > nbOutputs ? nbInputs : nbOutputs;
	m_bestSize.SetHeight((1 + m_maxParamsPerColumn) * 50); // MAGIC NUMBER here : we say 50 pixels per param and 50 pixels for the node's name

	// Defines the size of the widget
	SetSize(m_bestSize);

	// Add a sizer to manage the space inside the node
	wxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* titleText = new wxStaticText(this, wxID_ANY, "Title", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	verticalSizer->Add(titleText, 1, wxALL | wxEXPAND);

	for (int i = 0; i < m_maxParamsPerColumn; i++) {
		wxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
		// Add a pin if needed or an empty text to fill up the space if there's no pin
		if (i < nbInputs) {
			GUINodeParam* guiNodeInput = new GUINodeParam(this, m_node.GetInputs()[i]);
			horizontalSizer->Add(guiNodeInput, 1, wxALL | wxALIGN_CENTRE_VERTICAL);
		}else {
			horizontalSizer->Add(new wxStaticText(this, wxID_ANY, "EMPTY"), 2, wxALL | wxALIGN_CENTER_VERTICAL);
		}
		if (i < nbOutputs) {
			GUINodeParam* guiNodeOutput = new GUINodeParam(this, m_node.GetOutputs()[i]);
			horizontalSizer->Add(guiNodeOutput, 1, wxALL | wxALIGN_CENTRE_VERTICAL);
		}else{
			horizontalSizer->Add(new wxStaticText(this, wxID_ANY, ""), 2, wxALL | wxALIGN_CENTER_VERTICAL);
		}

		verticalSizer->Add(horizontalSizer, 1, wxALL | wxEXPAND);
	}

	SetSizer(verticalSizer);
	Layout();
	SetBackgroundColour(*wxGREEN);

	titleText->Bind(wxEVT_MOTION, &GUINode::OnMouseMotion, this);
	titleText->Bind(wxEVT_LEFT_DOWN, &GUINode::OnLeftMouseDown, this);
	titleText->Bind(wxEVT_LEFT_UP, &GUINode::OnLeftMouseUp, this);

	Bind(wxEVT_LEFT_DOWN, &GUINode::OnLeftMouseDown, this);
	Bind(wxEVT_LEFT_UP, &GUINode::OnLeftMouseUp, this);
	Bind(wxEVT_MOTION, &GUINode::OnMouseMotion, this);
	Bind(wxEVT_PAINT, &GUINode::OnPaint, this);

	((GraphView*)m_parent)->Bind(wxEVT_MOTION, &GUINode::OnMouseMotion, this);

}

wxSize GUINode::DoGetBestSize() const
{
	return m_bestSize;
}

void GUINode::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	/*wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

	int height = GetSize().GetHeight() - 1;
	int width = GetSize().GetWidth() - 1;
	if (gc)
	{
		// Draw the body
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
		gc->SetPen(wxPen(*wxBLACK, 1));
		gc->DrawRectangle(0, 0, width, height);
		
		delete gc;
	}
	*/
	event.Skip();
}

void GUINode::OnLeftMouseDown(wxMouseEvent& event)
{
	m_isDragging = true;
	m_firstDraggingPoint = ScreenToClient(ClientToScreen(event.GetPosition()));
}

void GUINode::OnLeftMouseUp(wxMouseEvent& event)
{
	m_isDragging = false;
	// Send the event to the GraphView
	event.SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
	m_graphView->OnMouseUp(event);
}

void GUINode::OnMouseMotion(wxMouseEvent& event)
{
	if (m_isDragging && event.LeftIsDown()) {
		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
		m_graphView->Redraw();
	}
	else
	{
		// Send the event to the GraphView, in case he wants to handle a wiring event
		event.SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
		m_graphView->OnMouseMotion(event);
	}
}

void GUINode::OnPinLeftMouseUp(wxMouseEvent& event)
{
	// If we release the node when the mouse is above a pin, we just stop the dragging
	if (m_isDragging)
		m_isDragging = false;
	else {
		event.SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
		m_graphView->OnMouseUp(event);
	}
}

void GUINode::OnPinMouseMotion(wxMouseEvent& event)
{
	// If we are moving the node and the mouse hover over a pin, continue moving
	if (m_isDragging) {
		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
		m_graphView->Refresh();
	}
	else { // If the mouse juste goes over the pin, we forward the event to graphView
		event.SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
		m_graphView->OnMouseMotion(event);
	}
}
