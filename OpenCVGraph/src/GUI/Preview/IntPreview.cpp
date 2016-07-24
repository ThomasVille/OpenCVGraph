#include "IntPreview.h"
#include <wx/sizer.h>
using namespace std;
IntPreview::IntPreview(wxWindow* parent, std::shared_ptr<Parameter> newValue):
	PreviewElement(parent)
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, newValue->GetName()+" : ");
	title->SetForegroundColour(*wxWHITE);
	bSizer1->Add(title, 0, wxALL, 5);

	m_text = new wxStaticText(this, wxID_ANY, "");
	m_text->SetForegroundColour(*wxWHITE);
	bSizer1->Add(m_text, 1, wxALL, 5);

	SetBackgroundColour(*wxBLUE);

	SetSizer(bSizer1);
	Layout();

	m_value = newValue;
	UpdateValue();
}

void IntPreview::UpdateValue()
{
	m_text->SetLabel(to_string(*static_pointer_cast<Data<int>>(m_value->GetData())->Get()));
}
