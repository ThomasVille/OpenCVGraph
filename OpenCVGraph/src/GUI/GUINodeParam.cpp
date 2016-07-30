#include "GUINodeParam.h"
#include "GraphView.h"
#include "GUINode.h"
#include "Resources.h"
void GUINodeParam::Draw(wxGraphicsContext * gc)
{
	wxSize fontSize = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT).GetPixelSize();
	// Draw the pin and the param name
	wxColor pinColor(m_parameter->GetType().r, m_parameter->GetType().g, m_parameter->GetType().b);
	gc->SetPen(wxPen(pinColor, 2));
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

}

void DrawCircle(wxGraphicsContext& gc, wxPoint p, int r)
{
	gc.DrawEllipse(p.x - r, p.y - r, 2*r, 2*r);
}
