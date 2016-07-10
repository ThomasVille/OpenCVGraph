#ifndef _GUI_GUINODE_H_
#define _GUI_GUINODE_H_

#include <wx/wx.h>

class GUINode : public wxControl
{
public:
	GUINode() : wxControl() { Init(); };
	GUINode(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& val = wxDefaultValidator) :
		wxControl(parent, winid, pos, size, style, val)
	{
		Init();
	}

protected:
	void Init();
	virtual wxSize DoGetBestSize() const;
	void OnPaint(wxPaintEvent&);

private:
	wxDECLARE_DYNAMIC_CLASS(GUINode);
};

#endif