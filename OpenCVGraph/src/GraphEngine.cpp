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

void GraphEngine::RunOneShot(Node* entryPoint)
{
	// Process all the nodes connected to the inputs
	for (auto input : entryPoint->GetInputs()) {
		for (auto param : input.second->GetLinkedNodes()) { // Iterates through the different linked nodes but an input should not have multiple links
			RunOneShot(param->GetParent());
		}
	}
	// Then process the current node
	entryPoint->GetComputer()(entryPoint->GetInputs(), entryPoint->GetOutputs());
	
}

void GraphEngine::AddNode(std::shared_ptr<Node> node)
{
	m_nodes.push_back(node);
	node->GetInitializer()(node->GetOutputs());
}
