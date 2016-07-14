#include "GUINode.h"
#include "GraphView.h"
wxIMPLEMENT_DYNAMIC_CLASS(GUINode, wxControl);

void GUINode::Init()
{
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

	// TODO Add horizontal sizers to distribute the space for each input/output
	for (int i = 0; i < m_maxParamsPerColumn; i++) {
		wxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
		// TODO change this text to a specific class GUINodeInput
		GUINodeParam* guiNodeInput = new GUINodeParam(this, i < nbInputs ? m_node.GetInputs()[i].GetName() : "", "I");
		GUINodeParam* guiNodeOutput = new GUINodeParam(this, i<nbOutputs ? m_node.GetOutputs()[i].GetName() : "", "O");


		horizontalSizer->Add(guiNodeInput, 1, wxALL | wxALIGN_CENTRE_VERTICAL);
		horizontalSizer->Add(guiNodeOutput, 1, wxALL | wxALIGN_CENTRE_VERTICAL);

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
	wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);

	int height = GetSize().GetHeight() - 1;
	int width = GetSize().GetWidth() - 1;
	int i = 0;
	if (gc)
	{
		// Draw the body
		gc->SetBrush(*wxRED_BRUSH);
		gc->SetPen(wxPen(*wxBLACK, 1));
		gc->DrawRoundedRectangle(0, 0, m_bestSize.GetWidth() - 1, m_bestSize.GetHeight() - 1, 10);
		
		gc->SetBrush(*wxBLUE_BRUSH);
		gc->SetFont(font, *wxBLACK);
		i = 0;
		// Draw the inputs
		for (InputParam p : m_node.GetInputs()) {
			gc->DrawEllipse(10, (i+0.5f)*height / m_maxParamsPerColumn, 25, 25);
			gc->DrawText(p.GetName(), 50, (i + 0.5f)*height / m_maxParamsPerColumn);
			i++;
		}
		i = 0;
		// Draw the outputs
		for (OutputParam p : m_node.GetOutputs()) {
			gc->DrawEllipse(width-50, (i+0.5f)*height / m_maxParamsPerColumn, 25, 25);
			gc->DrawText(p.GetName(), width-100, (i + 0.5f)*height / m_maxParamsPerColumn);
			i++;
		}

		delete gc;
	}*/

	
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
}

void GUINode::OnMouseMotion(wxMouseEvent& event)
{
	if (m_isDragging && event.LeftIsDown())
		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
}

void GUINode::OnPinMouseDown(wxMouseEvent& event)
{
	// In any case, if we click on a pin, we must say it to the GraphView above
	((GraphView*)m_parent)->OnPinMouseDown(this, m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
}

void GUINode::OnPinMouseUp(wxMouseEvent& event)
{
	// If we release the node when the mouse is above a pin, we just stop the dragging
	if (m_isDragging)
		m_isDragging = false;
	else
		((GraphView*)m_parent)->OnMouseUp(this, m_parent->ScreenToClient(ClientToScreen(event.GetPosition())));
}

void GUINode::OnPinMouseMotion(wxMouseEvent& event)
{
	// If we are moving the node and the mouse hover over a pin, continue moving
	if(m_isDragging)
		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
}
