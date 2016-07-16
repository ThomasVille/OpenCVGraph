#ifndef _GRAPHENGINE_H_
#define _GRAPHENGINE_H_
#include <memory>
#include "Node.h"
class GraphEngine
{
public:
	GraphEngine();
	~GraphEngine();

	void AddNode(std::shared_ptr<Node> node);
};

#endif