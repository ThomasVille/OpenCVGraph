#include "PreviewPanel.h"
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "../Resources.h"
#include "../../Node.h"
#include "../../Data.h"
#include "../MainFrame.h"

wxIMPLEMENT_DYNAMIC_CLASS(PreviewPanel, wxControl);
using namespace std;
using namespace cv;

void PreviewPanel::SetNode(shared_ptr<Node> node)
{
	if (m_node == node || node.unique() || node.use_count() == 0)
		return;
	m_node = node;

	// Check if the node is not empty
	// Update the interface and update the values in it
	m_pg->Clear();

	m_pg->Append(new wxPropertyCategory("Properties"));
	wxArrayString states;states.Add("Normal");states.Add("Entry point");
	auto stateP = new wxEnumProperty("State", wxPG_LABEL, states);
	// If the current node is the entry point, then we set State field to Entry point
	if (((MyFrame*)m_parent)->GetGraphView()->GetEntryPoint() == node)
		stateP->SetChoiceSelection(1);
	m_pg->Append(stateP);

	m_ioPanel->DestroyChildren();
	m_inputsPreview.clear();
	m_outputsPreview.clear();
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxStaticText* inputsText = new wxStaticText(m_ioPanel, wxID_ANY, "Inputs");
		sizer->Add(inputsText, 0, wxALL | wxEXPAND, 5);
		for (auto in : node->GetInputs()) {
			if (in.second->GetType().name == "int") {
				m_inputsPreview.push_back(new wxStaticText(m_ioPanel, wxID_ANY, in.first+" = empty"));
				sizer->Add(m_inputsPreview.back(), 0, wxALL | wxEXPAND, 5);
			}
			else if (in.second->GetType().name == "Mat") {
				m_inputsPreview.push_back(new wxStaticText(m_ioPanel, wxID_ANY, in.first+" = No display"));
				sizer->Add(m_inputsPreview.back(), 0, wxALL | wxEXPAND, 5);
			}
		}

		wxStaticText* outputsText = new wxStaticText(m_ioPanel, wxID_ANY, "Outputs");
		sizer->Add(outputsText, 0, wxALL | wxEXPAND, 5);
		for (auto out : node->GetOutputs()) {
			if (out.second->GetType().name == "int") {
				m_outputsPreview.push_back(new wxStaticText(m_ioPanel, wxID_ANY, out.first + " = empty"));
				sizer->Add(m_outputsPreview.back(), 0, wxALL | wxEXPAND, 5);
			}
			else if (out.second->GetType().name == "Mat") {
				// convert to bitmap to be used by the window to draw
				m_outputsPreview.push_back(new wxPanel(m_ioPanel));
				Mat tmp = *(static_pointer_cast<Data<Mat>>(out.second->GetData()))->Get().get();
				m_outputsPreview.back()->SetSize(tmp.cols, tmp.rows);
				// Do this to allow double buffering
				m_outputsPreview.back()->SetBackgroundStyle(wxBG_STYLE_PAINT);

				m_outputsPreview.back()->Bind(wxEVT_PAINT, [=](wxPaintEvent) {
					wxBufferedPaintDC dc(static_cast<wxPanel*>(m_outputsPreview.back()));
					wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
					if (gc) {
						Mat tmp;
						int w = m_outputsPreview.back()->GetClientSize().GetWidth();
						int h = m_outputsPreview.back()->GetClientSize().GetHeight();
						(static_pointer_cast<Data<Mat>>(out.second->GetData()))->Get()->copyTo(tmp);
						if (tmp.type() == CV_8UC1) {
							tmp.convertTo(tmp, CV_8UC3);
							Mat newSrc(tmp.size(), CV_MAKE_TYPE(tmp.type(), 3));

							int from_to[] = { 0,0, 0,1, 0,2 };

							cv::mixChannels(&tmp, 1, &newSrc, 1, from_to, 3);
							newSrc.copyTo(tmp);
						}
						cvtColor(tmp, tmp, COLOR_BGR2RGB);
						wxImage image(tmp.cols, tmp.rows, tmp.data, true);
						wxBitmap bitmap(image.Scale(w, h));
						gc->SetBrush(*wxWHITE_BRUSH);
						gc->SetPen(*wxWHITE_PEN);
						gc->DrawBitmap(bitmap, 0, 0, w, h);
						delete gc;
					}
					
				});
				sizer->Add(m_outputsPreview.back(), 0, wxALL | wxEXPAND | wxSHAPED, 5);
			}
		}
	m_ioPanel->SetSizer(sizer);


	Layout();
	Update();
}

void PreviewPanel::DeselectNode()
{
	m_pg->Clear();
	m_node.reset();
}

void PreviewPanel::OnPropertyGridChanged(wxPropertyGridEvent & event)
{
	wxPGProperty* property = event.GetProperty();
	// Do nothing if event did not have associated property
	if (!property)
		return;
	// GetValue() returns wxVariant, but it is converted transparently to
	// wxAny
	wxAny value = property->GetValue();
	// Also, handle the case where property value is unspecified
	if (value.IsNull())
		return;
	// Handle changes in values, as needed
	if (property->GetName() == "State")
		OnStateChanged(value.As<int>());

}

void PreviewPanel::OnStateChanged(int newState)
{
	// Asks the graphView to make the current node the entry point
	if (newState == 1)
		static_cast<MyFrame*>(m_parent)->GetGraphView()->MakeSelectedNodeEntryPoint();
}

void PreviewPanel::Update()
{
	if (m_node.use_count() != 0) {
		int i = 0;
		for (auto out : m_node->GetInputs()) {
			if (out.second->GetData() && out.second->GetType().name == "int") {
				static_cast<wxStaticText*>(m_inputsPreview.at(i))->SetLabel(out.first+" = "+ to_string(*(static_pointer_cast<Data<int>>(out.second->GetData()))->Get().get()));
			}
			i++;
		}
		i = 0;
		for (auto out : m_node->GetOutputs()) {
			if (out.second->GetData() && out.second->GetType().name == "int") {
				static_cast<wxStaticText*>(m_outputsPreview.at(i))->SetLabel(out.first + " = " + to_string(*(static_pointer_cast<Data<int>>(out.second->GetData()))->Get().get()));
			}
			i++;
		}
	}
	Refresh();
}

void PreviewPanel::Init()
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_pg = new wxPropertyGrid(this);
	bSizer1->Add(m_pg, 1, wxALL | wxEXPAND, 5);

	m_ioPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN);
	bSizer1->Add(m_ioPanel, 2, wxALL | wxEXPAND, 5);

	SetSizer(bSizer1);
	Layout();

	m_pg->Bind(wxEVT_PG_CHANGED, &PreviewPanel::OnPropertyGridChanged, this);
}