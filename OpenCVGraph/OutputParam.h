#ifndef _OUTPUTPARAM_H_
#define _OUTPUTPARAM_H_
#include <string>

class OutputParam
{
private:
	// Name of the parameter
	std::string m_name;
public:
	OutputParam(std::string name);
	~OutputParam();

	inline std::string GetName() {
		return m_name;
	}
};


#endif // !_OUTPUTPARAM_H_
