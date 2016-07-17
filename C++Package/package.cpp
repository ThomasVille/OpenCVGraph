#include <string>

extern "C" {
	__declspec(dllexport)
		int GetNumTypes() {
		return 42;
	}
}
