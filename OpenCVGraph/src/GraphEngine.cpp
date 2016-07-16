#include "GraphEngine.h"

GraphEngine::GraphEngine()
{
}


GraphEngine::~GraphEngine()
{
}

void GraphEngine::Init()
{
}

void GraphEngine::Stop()
{
}

void GraphEngine::RunOneShot(std::shared_ptr<Node> entryPoint)
{
}

void GraphEngine::AddNode(std::shared_ptr<Node> node)
{
	m_nodes.push_back(node);
}
