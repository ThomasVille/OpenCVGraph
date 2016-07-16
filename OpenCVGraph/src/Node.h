#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include "Parameter.h"
class Node
{
public:
	Node();
	Node(std::vector<Parameter>, std::vector<Parameter>);
	~Node();

	std::vector<Parameter> GetInputs() {
		return m_inputs;
	}
	std::vector<Parameter> GetOutputs() {
		return m_outputs;
	}

private:
	std::vector<Parameter> m_inputs;
	std::vector<Parameter> m_outputs;
};



#endif // !_NODE_H_