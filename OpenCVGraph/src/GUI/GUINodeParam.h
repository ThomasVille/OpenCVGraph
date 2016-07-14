#ifndef _GUI_GUINODEPARAM_H_
#define _GUI_GUINODEPARAM_H_
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Node.h"

class GUINodeParam : public wxControl
{
public:
	GUINodeParam():
		wxControl()
	{ Init(); };
	GUINodeParam(wxWindow *parent, std::string name, std::string type):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxDefaultValidator),
		m_name(name), m_type(type)
	{
		Init();
	}

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

	void OnPaint(wxPaintEvent&);
	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	void OnPinLeftMouseDown(wxMouseEvent&);
	void OnPinLeftMouseUp(wxMouseEvent&);
	void OnPinMouseMotion(wxMouseEvent& event);

	void OnNameLeftMouseDown(wxMouseEvent&);
	void OnNameLeftMouseUp(wxMouseEvent&);
	void OnNameMouseMotion(wxMouseEvent& event);

	wxStaticText* nameText;
	wxStaticText* pinImage;

	std::string m_name;
	std::string m_type;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINodeParam);
};

#endif