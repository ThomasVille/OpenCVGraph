#ifndef _MODELNODE_H_
#define _MODELNODE_H_
#include <memory>
#include <string>
#include <vector>
#include "Parameter.h"
class ModelNode
{
public:
	ModelNode(std::string name) : m_name(name){}
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

	std::vector<Parameter> GetInputs() {
		return m_inputs;
	}
	std::vector<Parameter> GetOutputs() {
		return m_outputs;
	}
	std::string GetName() {
		return m_name;
	}

	void SetInputs(std::vector<Parameter> in) {
		m_inputs = in;
	}
	void SetOutputs(std::vector<Parameter> out) {
		m_outputs = out;
	}
	void SetName(std::string name) {
		m_name = name;
	}
private:
	std::string m_name;
	std::vector<Parameter> m_inputs;
	std::vector<Parameter> m_outputs;
	std::vector<std::shared_ptr<ModelNode>> m_children;
};

#endif