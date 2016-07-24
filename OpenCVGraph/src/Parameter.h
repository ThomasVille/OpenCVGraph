#ifndef _PARAM_H_
#define _PARAM_H_
#include <string>
#include <vector>
#include <memory>
#include "BaseData.h"
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
	std::vector<std::shared_ptr<Parameter>> m_links;
	// Data stored in the parameter
	std::shared_ptr<BaseData> m_data;
	// Node we are the parameter of
	Node* m_parent;
public:
	Parameter(std::string name, Type type, ParamType paramType);
	~Parameter();

	// Returns true if the other parameter is compatible with this one
	bool IsCompatible(std::shared_ptr<Parameter> other);

	// Return true if connected to 1 node or if a default value is available
	bool HasEntry();

	inline std::string GetName() {
		return m_name;
	}
	inline Type GetType() {
		return m_type;
	}
	inline ParamType GetParamType() {
		return m_paramType;
	}
	inline std::shared_ptr<BaseData> GetData() {
		return m_data;
	}
	inline std::vector<std::shared_ptr<Parameter>> GetLinkedNodes() {
		return m_links;
	}
	inline Node* GetParent() {
		return m_parent;
	}
	inline void SetParent(Node* parent) {
		m_parent = parent;
	}

	/**
	* \brief Add a node to the list of nodes linked from/to this parameter.

	* \bug We can link to the same node twice or more.
	*/
	void AddLink(std::shared_ptr<Parameter> dstParam);

	void RemoveLinksTo(Node* node) {
		for(int i = 0; i < m_links.size(); i++)
			if (m_links[i]->GetParent() == node) {
				m_links.erase(m_links.begin() + i);
				i--;
			}
	}

	void AllocateData(std::shared_ptr<BaseData> initValue) {
		m_data = initValue;
	}
};


#endif // !_OUTPUTPARAM_H_
