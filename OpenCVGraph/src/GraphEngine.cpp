#include "GraphEngine.h"
#include "GUI\GraphView.h"
using namespace std;
bool GraphEngine::OneShotRecursive(Node * node)
{
	// Process all the nodes connected to the inputs
	for (auto input : node->GetInputs()) {
		if (!input.second->HasEntry()) { // Check if the input is connected to something or has a default value
			m_graphView->SimulationError("Input '" + input.first + "' missing in " + node->GetName() + "(" + to_string((int)node) + ")");
			return false;
		}
		for (auto param : input.second->GetLinkedNodes()) { // Iterates through the different linked nodes but an input should not have multiple links
			if (!OneShotRecursive(param->GetParent())) // If an input node failed, fail here too
				return false;
		}
	}
	// Then process the current node
	node->GetComputer()(node->GetInputs(), node->GetOutputs());
	return true;
}
GraphEngine::GraphEngine(GraphView* parent):
	m_graphView(parent)
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
	if (!entryPoint) {
		m_graphView->SimulationError("No entry point");
		return;
	}
	// Display Ok at the beginning and change during runtime if there was an error
	m_graphView->SimulationError("Graph Ok");
	OneShotRecursive(entryPoint);
}

void GraphEngine::AddNode(std::shared_ptr<Node> node)
{
	m_nodes.push_back(node);
	node->GetInitializer()(node->GetOutputs());
}

void GraphEngine::DeleteNode(shared_ptr<Node> node)
{
	for(unsigned int i = 0; i < m_nodes.size(); i++)
		if (m_nodes[i] == node) {
			m_nodes.erase(m_nodes.begin() + i);
			break;
		}

	for (auto n : m_nodes) {
		// Remove reference to this node in all the other nodes
		n->RemoveLinksTo(node);
	}
}
