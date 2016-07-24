#include "PreviewPanel.h"
#include "../Node.h"
#include "PreviewFactory.h"
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

	wxStaticText* m_label = new wxStaticText(this, wxID_ANY, wxT("Value :"), wxDefaultPosition, wxDefaultSize, 0);
	m_label->Wrap(-1);
	bSizer1->Add(m_label, 0, wxALL, 5);
	m_label->SetForegroundColour(*wxWHITE);

	// Create a text for each outputs of the node
	for (auto out : m_node->GetOutputs()) {
		m_valuesTexts.push_back(PreviewFactory::CreatePreviewElement(this, out.second));
		bSizer1->Add(m_valuesTexts.back(), 1, wxALL, 5);
	}

	SetSizer(bSizer1);
	Layout();
	SetBackgroundColour(*wxBLUE);
}