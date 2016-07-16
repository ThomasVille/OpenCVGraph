#include "GraphEngine.h"

GraphEngine::GraphEngine()
{
}


GraphEngine::~GraphEngine()
{
}

void GraphEngine::AddNode(std::shared_ptr<Node> node)
{
	m_nodes.push_back(node);
}
