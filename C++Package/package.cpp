#include <map>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../OpenCVGraph/src/Node.h"
#include "../OpenCVGraph/src/Parameter.h"
#include "../OpenCVGraph/src/BaseData.h"
#include "../OpenCVGraph/src/Data.h"

using namespace std;

template<typename T>
void SafeDeleter(T* p) {
	static int counter = 1;
	cout << "Safe delete n" << counter++ << endl;
	delete p;
}
template<typename T>
shared_ptr<T> CreateSafeShared(T model) {
	return shared_ptr<T>(new T(model));
}

extern "C"
{
	__declspec(dllexport) string* GetPackageName() {
		return new string("C++");
	}
	__declspec(dllexport) void DeletePackageName(string* name) {
		delete name;
	}
	__declspec(dllexport) vector<string>* GetNodesNames() {
		return new vector<string>{ "Int", "Add" };
	}
	__declspec(dllexport) void DeleteNodesNames(vector<string>* nodeNames) {
		delete nodeNames;
	}
	__declspec(dllexport) Data<Node>* CreateNode(string name) {
		if (name == "Int") {
			string name = "Int";
			ParamList inputs{};
			ParamList outputs{ {"value", CreateSafeShared<Parameter>(Parameter("value", Type("int"), OUTPUT_PARAM)) } };

			auto init = [](std::map<std::string, std::shared_ptr<BaseData>> outputs) {
				outputs["value"] = make_shared<Data<int>>(make_shared<int>(120));
			};

			auto computer = [](std::map<std::string, std::shared_ptr<BaseData>> in, std::map<std::string, std::shared_ptr<BaseData>> out) {
				(*static_pointer_cast<Data<int>>(out["value"])->Get().get()) = 42;
			};

			return new Data<Node>(CreateSafeShared<Node>(Node(name, inputs, outputs, init, computer)));
		}
		if (name == "Add") {
			string name = "Add";
			ParamList inputs{ {"a", CreateSafeShared<Parameter>(Parameter("a", Type("int"), INPUT_PARAM)) } , {"b", CreateSafeShared<Parameter>(Parameter("b", Type("int"), INPUT_PARAM)) } };
			ParamList outputs{ {"sum", CreateSafeShared<Parameter>(Parameter("sum", Type("int"), OUTPUT_PARAM)) }};

			auto init = [](std::map<std::string, std::shared_ptr<BaseData>> outputs) {
				outputs["sum"] = make_shared<Data<int>>(make_shared<int>(0));
			};

			auto computer = [](std::map<std::string, std::shared_ptr<BaseData>> in, std::map<std::string, std::shared_ptr<BaseData>> out) {
				(*static_pointer_cast<Data<int>>(out["value"])->Get()) = (*static_pointer_cast<Data<int>>(in["a"])->Get()) + (*static_pointer_cast<Data<int>>(in["b"])->Get());
			};

			return new Data<Node>(CreateSafeShared<Node>(Node(name, inputs, outputs, init, computer)));
		}
		return nullptr;
	}

	__declspec(dllexport) void DeleteNode(Data<Node>* node) {
		delete node;
	}
}


