#ifndef _GUI_PREVIEWPANEL_H_
#define _GUI_PREVIEWPANEL_H_
#include <memory>
#include <wx/sizer.h>
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
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
	{
		Init();
	}

	void SetNode(std::shared_ptr<Node> node);
	void DeselectNode();

	void Update();

protected:
	void Init();
	wxPropertyGrid* m_pg;
	std::shared_ptr<Node> m_node;

private:
	wxDECLARE_DYNAMIC_CLASS(PreviewPanel);
};

#endif