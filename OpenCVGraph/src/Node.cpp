#include "Node.h"

Node::Node(std::vector<Parameter> inputs, std::vector<Parameter> outputs):
	m_inputs(inputs), m_outputs(outputs)
{
}

Node::~Node()
{
}