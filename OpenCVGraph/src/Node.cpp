#include "Node.h"

Node::Node()
{
}

Node::Node(std::string name, std::vector<Parameter> inputs, std::vector<Parameter> outputs):
	m_name(name), m_inputs(inputs), m_outputs(outputs)
{
}

Node::~Node()
{
}