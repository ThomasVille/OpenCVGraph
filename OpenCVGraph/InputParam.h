#ifndef _INPUTPARAM_H_
#define _INPUTPARAM_H_
#include <string>

class InputParam
{
private:
	// Name of the parameter
	std::string m_name;

public:
	InputParam(std::string name);
	~InputParam();

	inline std::string GetName() {
		return m_name;
	}
};

#endif // !_INPUTPARAM_H_

