#ifndef _GUI_PREVIEWPANEL_H_
#define _GUI_PREVIEWPANEL_H_
#include <memory>
#include <wx/control.h>
#include <wx/stattext.h>
#include <wx/propgrid/propgrid.h>
#include "../../Parameter.h"

class Node;
class PreviewPanel : public wxControl
{
public:
	PreviewPanel():
		wxControl()
	{ 
		Init();
	};
	PreviewPanel(wxWindow *parent):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxCLIP_CHILDREN)
	{
		Init();
	}

	void SetNode(std::shared_ptr<Node> node);
	void DeselectNode();

	void OnPropertyGridChanged(wxPropertyGridEvent& event);

	/** Update the state of the selected node accordingly to the new state.
	* \param newState	Index of the choice in the "State" property in the property grid.
	*					0 means "Normal", 1 means "Entry point"
	*/
	void OnStateChanged(int newState);
	void Update();

protected:
	void Init();
	wxPropertyGrid* m_pg;
	wxPanel* m_ioPanel;
	std::vector<wxWindow*> m_inputsPreview;
	std::vector<wxWindow*> m_outputsPreview;

	std::shared_ptr<Node> m_node;

private:
	wxDECLARE_DYNAMIC_CLASS(PreviewPanel);
};

#endif