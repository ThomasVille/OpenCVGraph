#include "GUINodeParam.h"
#include "GraphView.h"
#include "GUINode.h"
wxIMPLEMENT_DYNAMIC_CLASS(GUINodeParam, wxControl);

void GUINodeParam::Init()
{
	// Compute the best width
	//m_bestSize.SetWidth(200); // Must be computed depending on the lengths of the inputs and outputs parameters
	// Compute the best height
	//int nbInputs = m_node.GetInputs().size();
	//int nbOutputs = m_node.GetOutputs().size();
	//m_maxParamsPerColumn = nbInputs > nbOutputs ? nbInputs : nbOutputs;
	//m_bestSize.SetHeight((1 + m_maxParamsPerColumn) * 50); // MAGIC NUMBER here : we say 50 pixels per param and 50 pixels for the node's name

	// Defines the size of the widget
	//SetSize(m_bestSize);

	
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	pinImage = new wxStaticText(this, wxID_ANY, m_type, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	pinImage->SetBackgroundColour(*wxRED); // Helps to visualize the space taken by the pin
	if (m_type == "I") {
		nameText = new wxStaticText(this, wxID_ANY, m_name, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
		sizer->Add(pinImage, 1, wxALL | wxALIGN_CENTER_VERTICAL); // From left to right, add the pin then the name for an input
		sizer->Add(nameText, 1, wxALL | wxALIGN_CENTER_VERTICAL);
	}
	else {
		nameText = new wxStaticText(this, wxID_ANY, m_name, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
		sizer->Add(nameText, 1, wxALL | wxALIGN_CENTER_VERTICAL); // From left to right, add the name then the pin for an output
		sizer->Add(pinImage, 1, wxALL | wxALIGN_CENTER_VERTICAL);
	}

	SetSizer(sizer);
	Layout();
	SetBackgroundColour(*wxBLUE);

	nameText->Bind(wxEVT_MOTION, &GUINodeParam::OnNameMouseMotion, this);
	nameText->Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnNameLeftMouseDown, this);
	nameText->Bind(wxEVT_LEFT_UP, &GUINodeParam::OnNameLeftMouseUp, this);
	pinImage->Bind(wxEVT_MOTION, &GUINodeParam::OnPinMouseMotion, this);
	pinImage->Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnPinLeftMouseDown, this);
	pinImage->Bind(wxEVT_LEFT_UP, &GUINodeParam::OnPinLeftMouseUp, this);

	Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnLeftMouseDown, this);
	Bind(wxEVT_LEFT_UP, &GUINodeParam::OnLeftMouseUp, this);
	Bind(wxEVT_MOTION, &GUINodeParam::OnMouseMotion, this);
	Bind(wxEVT_PAINT, &GUINodeParam::OnPaint, this);
}

wxSize GUINodeParam::DoGetBestSize() const
{
	return wxSize(100,100);
}

void GUINodeParam::OnPaint(wxPaintEvent &event)
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

void GUINodeParam::OnLeftMouseDown(wxMouseEvent& event)
{
	//m_isDragging = true;
	//m_firstDraggingPoint = ScreenToClient(ClientToScreen(event.GetPosition()));
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseDown(event);
}

void GUINodeParam::OnLeftMouseUp(wxMouseEvent& event)
{
	//m_isDragging = false;
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseUp(event);

}

void GUINodeParam::OnMouseMotion(wxMouseEvent& event)
{
//	if (m_isDragging && event.LeftIsDown())
//		SetPosition(m_parent->ScreenToClient(ClientToScreen(event.GetPosition())) - m_firstDraggingPoint);
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnMouseMotion(event);

}

void GUINodeParam::OnPinLeftMouseDown(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(pinImage->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnPinMouseDown(event);
}

void GUINodeParam::OnPinLeftMouseUp(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(pinImage->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnPinMouseUp(event);
}

void GUINodeParam::OnPinMouseMotion(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(pinImage->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnPinMouseMotion(event);
}

void GUINodeParam::OnNameLeftMouseDown(wxMouseEvent & event)
{
	// Convert from nameText coordinates to GUINode coordinates before sending it to GUINode
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(nameText->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseDown(event);
}

void GUINodeParam::OnNameLeftMouseUp(wxMouseEvent & event)
{
	// Convert from nameText coordinates to GUINode coordinates before sending it to GUINode
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(nameText->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseUp(event);
}

void GUINodeParam::OnNameMouseMotion(wxMouseEvent & event)
{
	// Convert from nameText coordinates to GUINode coordinates before sending it to GUINode
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(nameText->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnMouseMotion(event);
}
