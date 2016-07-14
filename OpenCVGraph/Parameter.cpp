#include "Parameter.h"

Parameter::Parameter():m_name(""),m_type(INPUT_PARAM)
{

}
Parameter::Parameter(std::string name, ParamType type):
	m_name(name), m_type(type)
{
}


Parameter::~Parameter()
{
}
