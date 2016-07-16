#ifndef _NODESPROVIDER_H_
#define _NODESPROVIDER_H_
#include <memory>
#include <string>
#include <vector>
#include "ModelNode.h"

class NodesProvider
{
public:
	NodesProvider();
	~NodesProvider();

	std::vector<std::shared_ptr<ModelNode>> GetItems();

private:
	std::vector<std::shared_ptr<ModelNode>> m_rootNodes;
};


#endif