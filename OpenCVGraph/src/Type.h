#ifndef _TYPE_H_
#define _TYPE_H_
#include <string>

struct Type {
	Type(std::string p_name, int p_r = 255, int p_g = 255, int p_b = 255) : name(p_name), r(p_r), g(p_g), b(p_b) {}

	bool CompatibleWith(Type& other) {
		return name == other.name;
	}

	std::string name = "empty";
	int r, g, b;
};

class TypeFactory
{
public:
	static Type GetType(std::string name) {
		if (name == "int") {
			return Type("int", 61, 42, 98);
		}
		else if (name == "Mat") {
			return Type("Mat", 230, 38, 43);
		}
		return Type("error-type", 255, 0, 0);
	}

private:

};

#endif