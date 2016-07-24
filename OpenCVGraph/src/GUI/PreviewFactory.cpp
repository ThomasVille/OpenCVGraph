#include "src\GUI\PreviewFactory.h"
#include "IntPreview.h"


PreviewElement* PreviewFactory::CreatePreviewElement(wxWindow* parent, std::shared_ptr<Parameter> param)
{
	if(param->GetType().name == "int")
		return new IntPreview(parent, param);

	return nullptr;
}
