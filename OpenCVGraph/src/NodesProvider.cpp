#include "NodesProvider.h"

using namespace std;

NodesProvider::NodesProvider()
{
	shared_ptr<ModelNode> node = make_shared<ModelNode>("C++");
	node->AddChild(make_shared<ModelNode>("If"));
	node->AddChild(make_shared<ModelNode>("While"));
	node->AddChild(make_shared<ModelNode>("Value"));
	node->AddChild(make_shared<ModelNode>("Slider"));
	m_rootNodes.push_back(node);

	node = make_shared<ModelNode>("OpenCV");
	node->AddChild(make_shared<ModelNode>("imread"));
	node->AddChild(make_shared<ModelNode>("imwrite"));
	node->AddChild(make_shared<ModelNode>("Mat"));
	node->AddChild(make_shared<ModelNode>("Scalar"));
	m_rootNodes.push_back(node);
}

NodesProvider::~NodesProvider()
{
}

std::vector<std::shared_ptr<ModelNode>> NodesProvider::GetItems()
{
	return m_rootNodes;
}
