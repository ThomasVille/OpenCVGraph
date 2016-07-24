#ifndef _GUI_PREVIEWPANEL_H_
#define _GUI_PREVIEWPANEL_H_
#include <memory>
#include <wx/control.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
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
	PreviewPanel(wxWindow *parent, std::shared_ptr<Node> node):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE),
		m_node(node)
	{
		Init();
	}

	void Update();

protected:
	void Init();
	std::vector<wxWindow*> m_valuesTexts;
	std::shared_ptr<Node> m_node;

private:
	wxDECLARE_DYNAMIC_CLASS(PreviewPanel);
};

#endif