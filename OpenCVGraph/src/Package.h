#ifndef _PACKAGE_H_
#define _PACKAGE_H_
#include <string>
#include <vector>
#include "Node.h"
#include "PDll.h"
#include "Data.h"
class Package : public PDLL
{
public:
	DECLARE_CLASS(Package)
	
	DECLARE_FUNCTION0(std::string*, GetPackageName)
	DECLARE_FUNCTION1(void, DeletePackageName, std::string*)
	DECLARE_FUNCTION0(std::vector<std::string>*, GetNodesNames)
	DECLARE_FUNCTION1(void, DeleteNodesName, std::vector<std::string>*)
	DECLARE_FUNCTION1(Data<Node>*, CreateNode, std::string)
	DECLARE_FUNCTION1(void, DeleteNode, Data<Node>*)
private:
};



#endif