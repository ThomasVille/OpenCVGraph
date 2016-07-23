#ifndef _PARAM_H_
#define _PARAM_H_
#include <string>
#include <vector>
#include <memory>
class Node;
enum ParamType {INPUT_PARAM, OUTPUT_PARAM};
struct Type {
	Type(std::string p_name) : name(p_name) {}

	bool CompatibleWith(Type& other) {
		return name == other.name;
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
	Type m_type;
	// Nodes it is linked to
	std::vector<std::shared_ptr<Node>> m_links;
public:
	Parameter(std::string name, Type type, ParamType paramType);
	~Parameter();

	// Returns true if the other parameter is compatible with this one
	bool IsCompatible(std::shared_ptr<Parameter> other);

	inline std::string GetName() {
		return m_name;
	}
	inline Type GetType() {
		return m_type;
	}
	inline ParamType GetParamType() {
		return m_paramType;
	}

	/**
	* \brief Add a node to the list of nodes linked from/to this parameter.

	* \bug We can link to the same node twice or more.
	*/
	void AddLink(std::shared_ptr<Node> dstNode);
};


#endif // !_OUTPUTPARAM_H_
