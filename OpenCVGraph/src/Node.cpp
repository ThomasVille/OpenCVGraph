#include "Node.h"

Node::Node(std::vector<InputParam> inputs, std::vector<OutputParam> outputs):
	m_inputs(inputs), m_outputs(outputs)
{
}

Node::~Node()
{
}