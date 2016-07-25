#include "GUINode.h"
#include "GraphView.h"
#include "Resources.h"
using namespace std;
void GUINode::Init()
{

	int nbInputs = m_node->GetInputs().size();
	int nbOutputs = m_node->GetOutputs().size();
	m_maxParamsPerColumn = nbInputs > nbOutputs ? nbInputs : nbOutputs;
	// MAGIC NUMBER here : we say 50 pixels per param + 50 pixels for the node's name + another 50 for the preview panel
	m_rect.SetHeight((2 + m_maxParamsPerColumn) * 50);
	m_rect.SetWidth(200);

	// Add a sizer to manage the space inside the node
	/*wxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* titleText = new wxStaticText(this, wxID_ANY, m_node->GetName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	verticalSizer->Add(titleText, 1, wxALL | wxEXPAND);

	// Add a preview panel into the node
	m_preview = new PreviewPanel(this, m_node);
	verticalSizer->Add(m_preview, 1, wxALL);

	// Add the parameters
	auto inputs = m_node->GetInputs();
	auto outputs = m_node->GetOutputs();
	ParamList::iterator inputIt = inputs.begin();
	ParamList::iterator outputIt = outputs.begin();
	for (int i = 0; i < m_maxParamsPerColumn; i++) {
		// The sizer we have to fit the two parameters in
		// Add a pin if needed or an empty text to fill up the space if there's no pin
		if (i < nbInputs) {
			m_params.push_back(make_shared<GUINodeParam>(this, inputIt->second, wxRect(GetPosition().x, i * 50 + GetPosition().y, 200, 50)));
			inputIt++;
		}
		if (i < nbOutputs) {
			m_params.push_back(make_shared<GUINodeParam>(this, outputIt->second, wxRect(GetPosition().x + GetSize().GetWidth() / 2, i * 50 + GetPosition().y, 200, 50)));
			outputIt++;
		}
	}
	*/
}

void GUINode::UpdatePreview()
{
	//m_preview->Update();
}

void GUINode::Draw(wxGraphicsContext * gc)
{
	// Draw the body
	gc->SetBrush(RES_NODE_MAIN_COLOR);
	gc->SetPen(RES_NODE_MAIN_COLOR);
	gc->DrawRectangle(m_rect.x, m_rect.y, m_rect.GetWidth(), m_rect.GetHeight());
	// Draw the name
	wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT).Larger();
	gc->SetFont(font, RES_NODE_TITLE_COLOR);
	gc->DrawText(m_node->GetName(), m_rect.x+5, m_rect.y+5);
	for (auto& p : m_params)
		p->Draw(gc);
}

void GUINode::StartDrag(wxPoint startingPoint)
{
	m_offset = m_rect.GetPosition() - startingPoint;
}

void GUINode::Drag(wxPoint p)
{
	SetPosition(p + m_offset);
}

void GUINode::SetPosition(wxPoint p)
{
	m_rect.x = p.x;
	m_rect.y = p.y;
}

wxRect GUINode::GetRect()
{
	return m_rect;
}

bool GUINode::IsInside(wxPoint p)
{
	return GetRect().Contains(p);
}
/*
void GUINode::OnRightMouseUp(wxMouseEvent & event)
{
	((GraphView*)m_parent)->DeleteNode(m_node.get());
	this->Destroy();
}*/
/*
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
*/