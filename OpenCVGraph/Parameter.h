#ifndef _PARAM_H_
#define _PARAM_H_
#include <string>

enum ParamType {INPUT_PARAM, OUTPUT_PARAM};

class Parameter
{
private:
	// Name of the parameter
	std::string m_name;
	// Type of parameter (input or output)
	ParamType m_type;
public:
	Parameter(std::string name, ParamType type);
	~Parameter();

	inline std::string GetName() {
		return m_name;
	}
};


#endif // !_OUTPUTPARAM_H_
