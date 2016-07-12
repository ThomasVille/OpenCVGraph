#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_

#include <wx/wx.h>
#include <wx/graphics.h>
class GUINode : public wxControl
{
public:
	GUINode() : wxControl() { Init(); };
	GUINode(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		const wxValidator& val = wxDefaultValidator) :
		wxControl(parent, winid, pos, size, wxBORDER_NONE, val)
	{
		Init();
	}

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	// Draws the node's body
	void OnPaint(wxPaintEvent&);
	void OnLeftMouseDown(wxMouseEvent&);
	void OnLeftMouseUp(wxMouseEvent&);
	void OnMouseMotion(wxMouseEvent& event);

	bool m_isDragging = false;
	wxPoint m_firstDraggingPoint;
private:
	wxDECLARE_DYNAMIC_CLASS(GUINode);
};

#endif