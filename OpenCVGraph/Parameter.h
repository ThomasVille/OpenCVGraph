#ifndef _PARAM_H_
#define _PARAM_H_
#include <string>
#include <memory>
enum ParamType {INPUT_PARAM, OUTPUT_PARAM};
struct Type {
	Type(std::string p_name) : name(p_name) {}

	bool CompatibleWith(std::shared_ptr<Type> other) {
		return name == other->name;
	}

	std::string name = "empty";
};
class Parameter
{
private:
	// Name of the parameter
	std::string m_name;
	// Type of parameter (input or output)
	ParamType m_paramType;
	// Type of the data
	std::shared_ptr<Type> m_type;
public:
	Parameter();
	Parameter(std::string name, std::shared_ptr<Type> type, ParamType paramType);
	~Parameter();

	// Returns true if the other parameter is compatible with this one
	bool IsCompatible(Parameter& other);

	inline std::string GetName() {
		return m_name;
	}
	inline std::shared_ptr<Type> GetType() {
		return m_type;
	}
	inline ParamType GetParamType() {
		return m_paramType;
	}
};


#endif // !_OUTPUTPARAM_H_
