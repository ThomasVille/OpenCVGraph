#ifndef _GRAPHENGINE_H_
#define _GRAPHENGINE_H_
#include <memory>
#include <vector>
#include "Node.h"
class GraphEngine
{
private:
	std::vector<std::shared_ptr<Node>> m_nodes;
public:
	GraphEngine();
	~GraphEngine();

	void Init();
	void Stop();

	// Run the graph from the entry point specified until the end and stops
	void RunOneShot(Node* entryPoint);
	
	void AddNode(std::shared_ptr<Node> node);
};

#endif