#include "GUINodeParam.h"
#include "GraphView.h"
#include "GUINode.h"
#include "Resources.h"
void GUINodeParam::Draw(wxGraphicsContext * gc)
{
	wxSize fontSize = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT).GetPixelSize();
	// Draw the pin and the param name
	gc->SetPen(wxPen(wxColor(255, 255, 255), 2));
	// If the pin is connected, fill the pin
	if(m_parameter->HasEntry())
		gc->SetBrush(wxBrush(wxColor(255, 255, 255)));
	else
		gc->SetBrush(*wxTRANSPARENT_BRUSH);

	// Draw the pin
	DrawCircle(*gc, GetPinPosition(), m_rect.GetHeight() / 6);

	// Draw the name
	if (m_parameter->GetParamType() == INPUT_PARAM)
		gc->DrawText(m_parameter->GetName(), m_rect.x + m_rect.GetWidth() / 6 + m_rect.GetHeight() / 2, m_rect.y + m_rect.GetHeight() / 2 - fontSize.GetY());
	else
		gc->DrawText(m_parameter->GetName(), m_rect.x, m_rect.y + m_rect.GetHeight()/2 - fontSize.GetY());

}

void GUINodeParam::Move(wxPoint offset)
{
	m_rect.x += offset.x;
	m_rect.y += offset.y;
}

wxPoint GUINodeParam::GetPinPosition()
{
	if (m_parameter->GetParamType() == INPUT_PARAM) // Return the middle of the left border
		return m_rect.GetPosition() + wxPoint(m_rect.GetSize().GetWidth() / 5, m_rect.GetSize().GetHeight() / 2);
	else // Return the middle of the right border
		return m_rect.GetPosition() + wxPoint(4 * m_rect.GetSize().GetWidth() / 5, m_rect.GetSize().GetHeight() / 2);
}

bool GUINodeParam::IsInsidePin(wxPoint p)
{
	return pow(GetPinPosition().x - p.x, 2) + pow(GetPinPosition().y - p.y, 2) < pow(m_rect.GetSize().GetHeight() / 2, 2);
}

std::shared_ptr<Parameter> GUINodeParam::GetParameter()
{
	return m_parameter;
}

GUINode * GUINodeParam::GetParent()
{
	return m_parent;
}

bool GUINodeParam::IsInside(wxPoint p)
{
	return m_rect.Contains(p);
}

void GUINodeParam::Init()
{
	/*wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	pinImage = new wxStaticText(this, wxID_ANY, "O", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);

	pinImage->SetBackgroundColour(RES_NODE_PIN_GOOD_STATE);

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

	nameText->Bind(wxEVT_MOTION, &GUINodeParam::OnNameMouseMotion, this);
	nameText->Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnNameLeftMouseDown, this);
	nameText->Bind(wxEVT_LEFT_UP, &GUINodeParam::OnNameLeftMouseUp, this);
	pinImage->Bind(wxEVT_MOTION, &GUINodeParam::OnPinMouseMotion, this);
	pinImage->Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnPinLeftMouseDown, this);
	pinImage->Bind(wxEVT_LEFT_UP, &GUINodeParam::OnPinLeftMouseUp, this);
	pinImage->Bind(wxEVT_RIGHT_UP, &GUINodeParam::OnPinRightMouseUp, this);

	Bind(wxEVT_LEFT_DOWN, &GUINodeParam::OnLeftMouseDown, this);
	Bind(wxEVT_LEFT_UP, &GUINodeParam::OnLeftMouseUp, this);
	Bind(wxEVT_MOTION, &GUINodeParam::OnMouseMotion, this);
	Bind(wxEVT_PAINT, &GUINodeParam::OnPaint, this);*/
}

void DrawCircle(wxGraphicsContext& gc, wxPoint p, int r)
{
	gc.DrawEllipse(p.x - r, p.y - r, 2*r, 2*r);
}
