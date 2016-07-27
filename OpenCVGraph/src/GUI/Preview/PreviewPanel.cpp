#include "PreviewPanel.h"
#include "../Resources.h"
#include "../../Node.h"
#include "../../Data.h"
wxIMPLEMENT_DYNAMIC_CLASS(PreviewPanel, wxControl);
using namespace std;

void PreviewPanel::SetNode(shared_ptr<Node> node)
{
	if (m_node == node || node.unique() || node.use_count() == 0)
		return;
	m_node = node;
	// Check if the node is not empty
	// Update the interface and update the values in it
	m_pg->Clear();
	m_pg->Append(new wxPropertyCategory("Inputs"));
	for (auto out : node->GetInputs()) {
		if (out.second->GetType().name == "int")
			m_pg->Append(new wxIntProperty(out.first, wxPG_LABEL, 0));
	}
	m_pg->Append(new wxPropertyCategory("Ouputs"));
	for (auto out : node->GetOutputs()) {
		if (out.second->GetType().name == "int")
			m_pg->Append(new wxIntProperty(out.first, wxPG_LABEL, 0));
	}
	Update();
}

void PreviewPanel::DeselectNode()
{
	m_pg->Clear();
	m_node.reset();
}

void PreviewPanel::Update()
{
	if (m_node.use_count() != 0) {
		for (auto out : m_node->GetInputs()) {
			if (out.second->GetData().use_count() != 0 && out.second->GetType().name == "int")
				m_pg->GetPropertyByName(out.first)->SetValueFromInt(*(static_pointer_cast<Data<int>>(out.second->GetData()))->Get().get());
		}
		for (auto out : m_node->GetOutputs()) {
			if (out.second->GetData().use_count() != 0 && out.second->GetType().name == "int")
				m_pg->GetPropertyByName(out.first)->SetValueFromInt(*(static_pointer_cast<Data<int>>(out.second->GetData()))->Get().get());
		}
	}
}

void PreviewPanel::Init()
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_pg = new wxPropertyGrid(this);
	bSizer1->Add(m_pg, 1, wxALL | wxEXPAND, 5);

	SetSizer(bSizer1);
	Layout();
}