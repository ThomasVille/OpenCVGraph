#include "GUINodeParam.h"
#include "GraphView.h"
#include "GUINode.h"
wxIMPLEMENT_DYNAMIC_CLASS(GUINodeParam, wxControl);

wxPoint GUINodeParam::GetPinPosition()
{
	if(m_parameter->GetParamType() == INPUT_PARAM) // Return the middle of the left border of the image
		return m_graphView->ScreenToClient(ClientToScreen( pinImage->GetPosition()+wxPoint(0,pinImage->GetRect().GetHeight()/2) ));
	else // Return the middle of the right border of the image
		return m_graphView->ScreenToClient(ClientToScreen(pinImage->GetPosition() + wxPoint(pinImage->GetRect().GetWidth(), pinImage->GetRect().GetHeight() / 2)));
}

std::shared_ptr<Parameter> GUINodeParam::GetParameter()
{
	return m_parameter;
}

void GUINodeParam::Init()
{
	m_graphView = (GraphView*)(((GUINode*)m_parent)->GetParent());

	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	pinImage = new wxStaticText(this, wxID_ANY, "O", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	pinImage->SetBackgroundColour(*wxRED); // Helps to visualize the space taken by the pin
	if (m_parameter->GetParamType() == INPUT_PARAM) {
		nameText = new wxStaticText(this, wxID_ANY, m_parameter->GetName(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
		sizer->Add(pinImage, 1, wxALL | wxALIGN_CENTER_VERTICAL); // From left to right, add the pin then the name for an input
		sizer->Add(nameText, 1, wxALL | wxALIGN_CENTER_VERTICAL);
	}
	else {
		nameText = new wxStaticText(this, wxID_ANY, m_parameter->GetName(), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
		sizer->Add(nameText, 1, wxALL | wxALIGN_CENTER_VERTICAL); // From left to right, add the name then the pin for an output
		sizer->Add(pinImage, 1, wxALL | wxALIGN_CENTER_VERTICAL);
	}
	nameText->SetForegroundColour(*wxWHITE);

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
		if(m_parameter->IsCompatible(m_graphView->GetSelectedPin()->GetParameter()))
			m_graphView->AddWire(this, m_graphView->GetSelectedPin());
	}
	// Convert from pinImage coordinates to GUINode coordinates before sending it to GUINode
	event.SetPosition(((GUINode*)m_parent)->ScreenToClient(pinImage->ClientToScreen(event.GetPosition())));
	((GUINode*)m_parent)->OnPinLeftMouseUp(event);
}

void GUINodeParam::OnPinMouseMotion(wxMouseEvent& event)
{
	if (m_graphView->isWiring()) { // If we are wiring right now, check the link and tell the GraphView if it is allowed
		// If the two pins are not compatible, error
		if (!m_parameter->IsCompatible(m_graphView->GetSelectedPin()->GetParameter())) {
			m_graphView->SetLinkState(ERROR_SAME_WAY);
		}
		else {
			m_graphView->SetLinkState(LINK_OK);
		}
	}
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
