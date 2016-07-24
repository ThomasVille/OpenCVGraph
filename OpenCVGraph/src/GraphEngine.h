#ifndef _GRAPHENGINE_H_
#define _GRAPHENGINE_H_
#include <memory>
#include <vector>
#include "Node.h"
class GraphView;
class GraphEngine
{
private:
	std::vector<std::shared_ptr<Node>> m_nodes;
	GraphView* m_graphView;

	void OneShotRecursive(Node* node);
public:
	GraphEngine(GraphView* parent);
	~GraphEngine();

	void Init();
	void Stop();

	// Run the graph from the entry point specified until the end and stops
	void RunOneShot(Node* entryPoint);
	
	void AddNode(std::shared_ptr<Node> node);
	void DeleteNode(Node* node);
};

#endif