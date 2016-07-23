#include "Node.h"

Node::Node()
{
}

Node::Node(std::string name, ParamList inputs, ParamList outputs, InitializerType initializer, ComputerType computer, PreviewPanelMakerType previewMaker):
	m_name(name), m_inputs(inputs), m_outputs(outputs), m_initializer(initializer), m_computer(computer), m_previewPanelMaker(previewMaker)
{
}

Node::~Node()
{
}