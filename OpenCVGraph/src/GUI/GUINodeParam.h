#ifndef _GUI_GUINODEPARAM_H_
#define _GUI_GUINODEPARAM_H_
#include <memory>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "../Parameter.h"

class GraphView;
enum LinkState { ERROR_SAME_WAY, LINK_OK, END_MISSING };
class GUINodeParam : public wxControl
{
public:
	GUINodeParam():
		wxControl(), m_parameter(std::make_shared<Parameter>("empty", Type("empty"), INPUT_PARAM))
	{ 
		Init();
	};
	GUINodeParam(wxWindow *parent, std::shared_ptr<Parameter> param):
		wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE, wxDefaultValidator),
		m_parameter(param)
	{
		Init();
	}

	// Return the position of the pin in *GraphView* coordinates
	wxPoint GetPinPosition();

	std::shared_ptr<Parameter> GetParameter();

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;

	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	void OnPinRightMouseUp(wxMouseEvent& event);
	void OnPinLeftMouseDown(wxMouseEvent&);
	void OnPinLeftMouseUp(wxMouseEvent&);
	void OnPinMouseMotion(wxMouseEvent& event);

	void OnNameLeftMouseDown(wxMouseEvent&);
	void OnNameLeftMouseUp(wxMouseEvent&);
	void OnNameMouseMotion(wxMouseEvent& event);

	wxStaticText* nameText;
	wxStaticText* pinImage;

	std::shared_ptr<Parameter> m_parameter;

	// Pointer to the GraphView
	// For convenience
	GraphView* m_graphView;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINodeParam);
};

#endif