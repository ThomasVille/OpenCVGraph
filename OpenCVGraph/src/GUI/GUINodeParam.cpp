#include "GUINodeParam.h"
#include "GraphView.h"
#include "GUINode.h"
wxIMPLEMENT_DYNAMIC_CLASS(GUINodeParam, wxControl);

wxPoint GUINodeParam::GetPinPosition()
{
	return m_graphView->ScreenToClient(ClientToScreen(pinImage->GetPosition()));
}

void GUINodeParam::Init()
{
	m_graphView = (GraphView*)(((GUINode*)m_parent)->GetParent());
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
	pinImage = new wxStaticText(this, wxID_ANY, "O", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	pinImage->SetBackgroundColour(*wxRED); // Helps to visualize the space taken by the pin
	if (m_parameter.GetType() == INPUT_PARAM) {
		nameText = new wxStaticText(this, wxID_ANY, m_parameter.GetName(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
		sizer->Add(pinImage, 1, wxALL | wxALIGN_CENTER_VERTICAL); // From left to right, add the pin then the name for an input
		sizer->Add(nameText, 1, wxALL | wxALIGN_CENTER_VERTICAL);
	}
	else {
		nameText = new wxStaticText(this, wxID_ANY, m_parameter.GetName(), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
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

void GUINodeParam::OnLeftMouseDown(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseDown(event);
}

void GUINodeParam::OnLeftMouseUp(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnLeftMouseUp(event);

}

void GUINodeParam::OnMouseMotion(wxMouseEvent& event)
{
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnMouseMotion(event);
}

void GUINodeParam::OnPinLeftMouseDown(wxMouseEvent& event)
{
	// Convert from pinImage coordinates to GUINode coordinates before sending it to GUINode
	m_graphView->OnPinLeftMouseDown(this, GetPinPosition());
}

void GUINodeParam::OnPinLeftMouseUp(wxMouseEvent& event)
{
	// If we are wiring two pins together (and thus, this is a second one)
	// We add the wire between the twos after checking if it's possible
	if (m_graphView->isWiring()) {
		m_graphView->AddWire(this, m_graphView->GetSelectedPin());
	}
	// Convert from pinImage coordinates to GUINode coordinates before sending it to GUINode
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(pinImage->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnPinLeftMouseUp(event);
}

void GUINodeParam::OnPinMouseMotion(wxMouseEvent& event)
{
	// Convert from pinImage coordinates to GUINode coordinates before sending it to GUINode
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
