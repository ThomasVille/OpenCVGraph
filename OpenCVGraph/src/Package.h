#ifndef _PACKAGE_H_
#define _PACKAGE_H_
#include <string>

class Package
{
public:
	Package(std::string dllPath);
	~Package();

private:
	std::string m_dllPath;
};



#endif