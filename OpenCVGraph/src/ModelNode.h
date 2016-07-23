#ifndef _MODELNODE_H_
#define _MODELNODE_H_
#include <memory>
#include <string>
#include <vector>
#include "Parameter.h"
#include "Node.h"
class ModelNode
{
public:
	ModelNode(std::string nodeName, std::string pkgName) : m_name(nodeName), m_pkgName(pkgName){}
	~ModelNode() {}

	bool HasChildren() {
		return !m_children.empty();
	}
	std::vector<std::shared_ptr<ModelNode>> GetChildren() {
		return m_children;
	}
	void AddChild(std::shared_ptr<ModelNode> newNode) {
		m_children.push_back(newNode);
	}
	std::string GetName() {
		return m_name;
	}
	std::string GetPkgName() {
		return m_pkgName;
	}
private:
	std::string m_name;
	std::string m_pkgName;
	std::vector<std::shared_ptr<ModelNode>> m_children;
};

#endif