#pragma once
#include <memory>
#include <wx/control.h>
#include "../../Parameter.h"
class PreviewElement : public wxControl
{
protected:
	// Parameter to show
	std::shared_ptr<Parameter> m_value;
public:
	PreviewElement(wxWindow* parent) : wxControl(parent, wxID_ANY) {

	}
	// Show the new value of the parameter
	virtual void UpdateValue() = 0;
};

