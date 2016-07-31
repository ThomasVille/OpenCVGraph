#ifndef _PACKAGE_H_
#define _PACKAGE_H_
#include <string>
#include <vector>
#include "Node.h"
#include "PDll.h"
#include "Data.h"

class wxPanel;
class wxWindow;
class Package : public PDLL
{
public:
	DECLARE_CLASS(Package)
	DECLARE_FUNCTION1(void, GetNodesNames, std::vector<std::string>&)
	DECLARE_FUNCTION2(void, NodeFactory, std::string, std::shared_ptr<Node>&)
private:
};



#endif