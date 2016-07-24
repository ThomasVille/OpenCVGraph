#include "Parameter.h"
#include "Node.h"
/*
Parameter::Parameter():m_paramType(INPUT_PARAM)
{

}*/
Parameter::Parameter(std::string name, Type type, ParamType paramType):
	m_name(name), m_type(type), m_paramType(paramType)
{
}


Parameter::~Parameter()
{
}

bool Parameter::IsCompatible(std::shared_ptr<Parameter> other)
{
	// Check if the parent node is different
	if (m_parent == other->GetParent())
		return false;
	// Check if the input is free
	if ((m_paramType == INPUT_PARAM && !m_links.empty()) || (other->GetParamType() == INPUT_PARAM && !other->GetLinkedNodes().empty()))
		return false;
	// Check if we are linking an input with an output
	if (GetParamType() == other->GetParamType())
		return false;
	// Check if the types are compatible
	if (!GetType().CompatibleWith(other->GetType()))
		return false;

	return true;
}

void Parameter::AddLink(std::shared_ptr<Parameter> dstParam)
{
	// Link to the node
	m_links.push_back(dstParam);
	// Set the the node to be the data source only if this param is the input
	if(m_paramType == INPUT_PARAM)
		m_data = dstParam->GetData();
}
