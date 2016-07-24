#pragma once
#include <memory>
#include <wx/stattext.h>
#include "PreviewElement.h"
#include "../../Data.h"

class IntPreview :
	public PreviewElement
{
private:
	wxStaticText* m_text;
public:
	IntPreview(wxWindow* parent, std::shared_ptr<Parameter> value);
	void UpdateValue();
};

