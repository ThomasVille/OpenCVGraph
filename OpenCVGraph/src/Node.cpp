#include "Node.h"

Node::Node()
{
}

Node::Node(std::string name, ParamList inputs, ParamList outputs, InitializerType initializer, ComputerType computer):
	m_name(name), m_inputs(inputs), m_outputs(outputs), m_initializer(initializer), m_computer(computer)
{
	for (auto& param : m_inputs)
		param.second->SetParent(this);
	for (auto& param : m_outputs)
		param.second->SetParent(this);
}

Node::~Node()
{
}