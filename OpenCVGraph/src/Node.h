#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include "Parameter.h"
class Node
{
public:
	Node();
	Node(std::string name, std::vector<Parameter>, std::vector<Parameter>);
	~Node();

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
	std::vector<Parameter> m_inputs;
	std::vector<Parameter> m_outputs;
	std::string m_name;
};



#endif // !_NODE_H_