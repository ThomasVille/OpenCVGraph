#pragma once
#include <string>
#include <memory>
#include "PreviewElement.h"
#include "../../Parameter.h"

class PreviewFactory
{
public:
	PreviewFactory(){}
	~PreviewFactory(){}
	static PreviewElement* CreatePreviewElement(wxWindow* parent, std::shared_ptr<Parameter> param);
};

