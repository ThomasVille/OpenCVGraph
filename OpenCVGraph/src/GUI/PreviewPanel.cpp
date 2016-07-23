#include "PreviewPanel.h"

wxIMPLEMENT_DYNAMIC_CLASS(PreviewPanel, wxControl);


void PreviewPanel::Init()
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* m_label = new wxStaticText(this, wxID_ANY, wxT("Value :"), wxDefaultPosition, wxDefaultSize, 0);
	m_label->Wrap(-1);
	bSizer1->Add(m_label, 0, wxALL, 5);

	m_valueText = new wxStaticText(this, wxID_ANY, wxT("Awesome value"), wxDefaultPosition, wxDefaultSize, 0);
	m_valueText->Wrap(-1);
	bSizer1->Add(m_valueText, 0, wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	SetSizer(bSizer1);
	Layout();
	SetBackgroundColour(*wxBLUE);
}