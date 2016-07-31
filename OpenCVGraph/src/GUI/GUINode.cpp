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

	/*
	m_preview = new PreviewPanel(this, m_node);
	*/
	// Add the parameters
	auto inputs = m_node->GetInputs();
	auto outputs = m_node->GetOutputs();
	ParamList::iterator inputIt = inputs.begin();
	ParamList::iterator outputIt = outputs.begin();
	for (int i = 0; i < m_maxParamsPerColumn; i++) {
		// The sizer we have to fit the two parameters in
		// Add a pin if needed or an empty text to fill up the space if there's no pin
		if (i < nbInputs) {
			m_params.push_back(make_shared<GUINodeParam>(this, m_graphView, inputIt->second, wxRect(m_rect.x, (2+i) * 50 + m_rect.y, 100, 50)));
			inputIt++;
		}
		if (i < nbOutputs) {
			m_params.push_back(make_shared<GUINodeParam>(this, m_graphView, outputIt->second, wxRect(m_rect.x + m_rect.GetWidth() / 2, (2+i) * 50 + m_rect.y, 100, 50)));
			outputIt++;
		}
	}
	
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
	// Draw the parameters
	for (auto& p : m_params)
		p->Draw(gc);
	// Draw the highlight if the node is selected
	if (m_isSelected) {
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
		gc->SetPen(wxPen(RES_NODE_HIGHLIGHT, 1));
		gc->DrawRectangle(m_rect.x - 1,	m_rect.y - 1, m_rect.GetWidth() + 1, m_rect.GetHeight() + 1);
	}

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
	// Move the parameters first
	for (auto param : m_params)
		param->Move(p - m_rect.GetPosition());

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

void GUINode::Select()
{
	m_isSelected = true;
}

void GUINode::Deselect()
{
	m_isSelected = false;
}
