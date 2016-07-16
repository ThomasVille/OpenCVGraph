#include "Parameter.h"

Parameter::Parameter():m_paramType(INPUT_PARAM)
{

}
Parameter::Parameter(std::string name, std::shared_ptr<Type> type, ParamType paramType):
	m_name(name), m_type(type), m_paramType(paramType)
{
}


Parameter::~Parameter()
{
}

bool Parameter::IsCompatible(Parameter & other)
{
	return ( GetParamType() != other.GetParamType() ) && ( GetType()->CompatibleWith(other.GetType()) );
}
