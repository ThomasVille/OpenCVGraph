#include "NodesProvider.h"
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/log.h>
using namespace std;


NodesProvider::NodesProvider()
{
	
}

NodesProvider::~NodesProvider()
{
}

void NodesProvider::Init()
{
	// List all the packages available
	wxString filename;
	wxDir dir(wxGetCwd());
	// Check that the object is created and that the "packages" directory exists 
	if (!dir.IsOpened() || !dir.Open("packages")) {
		wxLogDebug(dir.GetName());
		return;
	}
	
	// Traverse the packages directory and add each package to the package list
	bool cont = dir.GetFirst(&filename, "", wxDIR_DIRS);
	while (cont)
	{
		wxLogDebug("Load Package : %s", filename);
		// Implementation specific here
		m_packages.push_back(make_shared<Package>("packages/"+filename.ToStdString()+"/package.dll"));
		cont = dir.GetNext(&filename);
	}

	// Constructs the Types list
	m_types["int"] = make_shared<Type>("int");
	m_types["string"] = make_shared<Type>("string");
	m_types["bool"] = make_shared<Type>("bool");
	m_types[".flow"] = make_shared<Type>(".flow");

	// Constructs the nodes description list
	shared_ptr<ModelNode> node = make_shared<ModelNode>("C++");
	auto tmp = make_shared<ModelNode>("If");
	tmp->SetInputs({ Parameter("Condition", m_types["bool"], INPUT_PARAM) });
	tmp->SetOutputs({ Parameter("True", m_types[".flow"], OUTPUT_PARAM), Parameter("False", m_types[".flow"], OUTPUT_PARAM) });
	node->AddChild(tmp);
	tmp = make_shared<ModelNode>("String");
	tmp->SetOutputs({ Parameter("Value", m_types["string"], OUTPUT_PARAM), Parameter("Flow", m_types[".flow"], OUTPUT_PARAM) });
	node->AddChild(tmp);
	tmp = make_shared<ModelNode>("Concatenate");
	tmp->SetInputs({ Parameter("First", m_types["string"], INPUT_PARAM), Parameter("Second", m_types["string"], INPUT_PARAM) });
	tmp->SetOutputs({ Parameter("Result", m_types["string"], OUTPUT_PARAM), Parameter("Flow", m_types[".flow"], OUTPUT_PARAM) });
	node->AddChild(tmp);
	m_rootNodes.push_back(node);

	node = make_shared<ModelNode>("OpenCV");
	node->AddChild(make_shared<ModelNode>("imread"));
	node->AddChild(make_shared<ModelNode>("imwrite"));
	node->AddChild(make_shared<ModelNode>("Mat"));
	node->AddChild(make_shared<ModelNode>("Scalar"));
	m_rootNodes.push_back(node);
}

std::vector<std::shared_ptr<ModelNode>> NodesProvider::GetItems()
{
	return m_rootNodes;
}

std::shared_ptr<Node> NodesProvider::GetNewNode(std::shared_ptr<ModelNode> description)
{
	shared_ptr<Node> tmp = make_shared<Node>();
	tmp->SetName(description->GetName());
	tmp->SetInputs(description->GetInputs());
	tmp->SetOutputs(description->GetOutputs());
	return tmp;
}
