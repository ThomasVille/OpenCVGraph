#include "NodesProvider.h"
#include <wx/log.h>
#include <wx/filefn.h>
#include <wx/dir.h>
#include "Package.h"
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

		m_packages[filename.ToStdString()] = make_shared<Package>(string("packages/"+filename.ToStdString()+"/package.dll").c_str());
		// Create the package node in the tree
		shared_ptr<ModelNode> packageNode = make_shared<ModelNode>(filename.ToStdString(), filename.ToStdString());
		// Add a node for each nodes we can create with this package
		vector<string> nodesName;
		m_packages[filename.ToStdString()]->GetNodesNames(nodesName);
		for (auto nodeName : nodesName) {
			packageNode->AddChild(make_shared<ModelNode>(nodeName, filename.ToStdString()));
		}
		// Add the package node to the tree
		m_rootNodes.push_back(packageNode);
		// Iterate to the next package
		cont = dir.GetNext(&filename);
	}
}

std::vector<std::shared_ptr<ModelNode>> NodesProvider::GetItems()
{
	return m_rootNodes;
}

std::shared_ptr<Node> NodesProvider::GetNewNode(std::shared_ptr<ModelNode> description)
{
	// Get the new node from the DLL
	shared_ptr<Node> newNode;
	m_packages[description->GetPkgName()]->NodeFactory(description->GetName(), newNode);
	return	newNode;
}
