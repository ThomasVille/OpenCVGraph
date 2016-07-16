#include "NodesProvider.h"

using namespace std;

NodesProvider::NodesProvider()
{
	// Constructs the nodes description list
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

	// Constructs the Types list
	m_types["int"] = make_shared<Type>("int");
	m_types["string"] = make_shared<Type>("string");
	m_types["UMat"] = make_shared<Type>("UMat");
}

NodesProvider::~NodesProvider()
{
}

std::vector<std::shared_ptr<ModelNode>> NodesProvider::GetItems()
{
	return m_rootNodes;
}

std::shared_ptr<Node> NodesProvider::GetNewNode(std::shared_ptr<ModelNode> description)
{
	return make_shared<Node>(vector<Parameter>({Parameter("test", m_types["int"], INPUT_PARAM)}), vector<Parameter>({ Parameter("test", m_types["int"], OUTPUT_PARAM) }));
}
