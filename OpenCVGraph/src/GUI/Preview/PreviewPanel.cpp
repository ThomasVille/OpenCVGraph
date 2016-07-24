#include "PreviewPanel.h"
#include "PreviewFactory.h"
#include "../../Node.h"
wxIMPLEMENT_DYNAMIC_CLASS(PreviewPanel, wxControl);


void PreviewPanel::Update()
{
	for (auto value : m_valuesTexts)
		((PreviewElement*)value)->UpdateValue();
}

void PreviewPanel::Init()
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	// Create a text for each outputs of the node
	for (auto out : m_node->GetOutputs()) {
		m_valuesTexts.push_back(PreviewFactory::CreatePreviewElement(this, out.second));
		bSizer1->Add(m_valuesTexts.back(), 1, wxALL, 5);
	}

	SetSizer(bSizer1);
	Layout();
	SetBackgroundColour(*wxBLUE);
}