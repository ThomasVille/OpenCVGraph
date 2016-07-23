#ifndef _GUI_PREVIEWPANEL_H_
#define _GUI_PREVIEWPANEL_H_
#include <memory>
#include <wx/control.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include "../Parameter.h"

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

protected:
	void Init();

	wxStaticText* m_valueText;

private:
	wxDECLARE_DYNAMIC_CLASS(PreviewPanel);
};

#endif