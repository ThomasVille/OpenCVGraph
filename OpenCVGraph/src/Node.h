#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include "InputParam.h"
#include "OutputParam.h"

class Node
{
public:
	Node(std::vector<InputParam>, std::vector<OutputParam>);
	~Node();

	std::vector<InputParam> GetInputs() {
		return m_inputs;
	}
	std::vector<OutputParam> GetOutputs() {
		return m_outputs;
	}

private:
	std::vector<InputParam> m_inputs;
	std::vector<OutputParam> m_outputs;
};



#endif // !_NODE_H_