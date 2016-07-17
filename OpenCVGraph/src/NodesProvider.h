#ifndef _NODESPROVIDER_H_
#define _NODESPROVIDER_H_
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "ModelNode.h"
#include "Node.h"
#include "Package.h"

class NodesProvider
{
public:
	NodesProvider();
	~NodesProvider();

	void Init();

	std::vector<std::shared_ptr<ModelNode>> GetItems();

	// Factory method : returns a new node following the node description
	std::shared_ptr<Node> GetNewNode(std::shared_ptr<ModelNode> description);

private:
	std::vector<std::shared_ptr<Package>> m_packages;

	// First level of nodes
	// ModelNodes containing other nodes are like folders
	std::vector<std::shared_ptr<ModelNode>> m_rootNodes;

	// Types available
	// They are managed by the NodesProvider
	std::map<std::string, std::shared_ptr<Type>> m_types;
};


#endif