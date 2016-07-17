#ifndef _PACKAGE_H_
#define _PACKAGE_H_
#include <string>
#include "PDll.h"

class Package : public PDLL
{
public:
	DECLARE_CLASS(Package)
	DECLARE_FUNCTION0(int, GetNumTypes)
private:
};



#endif