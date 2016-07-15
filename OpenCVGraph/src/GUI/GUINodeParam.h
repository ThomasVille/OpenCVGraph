#ifndef _GUI_GUINODEPARAM_H_
#define _GUI_GUINODEPARAM_H_
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Parameter.h"

class GraphView;

class GUINodeParam : public wxControl
{
public:
	GUINodeParam():
		wxControl()
	{ Init(); };
	GUINodeParam(wxWindow *parent, Parameter param):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxDefaultValidator),
		m_parameter(param)
	{
		Init();
	}

	// Return the position of the pin in *GraphView* coordinates
	wxPoint GetPinPosition();

	Parameter GetParameter();

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

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

	Parameter m_parameter;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINodeParam);
};

#endif