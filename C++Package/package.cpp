#include <map>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../OpenCVGraph/src/Node.h"
#include "../OpenCVGraph/src/Parameter.h"
#include "../OpenCVGraph/src/Data.h"

using namespace std;

extern "C"
{
	__declspec(dllexport) void GetNodesNames(vector<string>& names) {
		names = { "Int", "Add" };
	}
	__declspec(dllexport) void NodeFactory(string name, shared_ptr<Node>& node) {
		if (name == "Int") {
			string name = "Int";
			ParamList inputs{};
			ParamList outputs{ {"value", make_shared<Parameter>("value", TypeFactory::GetType("int"), OUTPUT_PARAM) } };

			InitializerType init = [](ParamList outputs) {
				outputs["value"]->AllocateData(make_shared<Data<int>>(make_shared<int>(5)));
			};

			ComputerType computer = [](ParamList in, ParamList out) {
			};

			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
		if (name == "Add") {
			string name = "Add";
			ParamList inputs{ {"a", make_shared<Parameter>("a", TypeFactory::GetType("int"), INPUT_PARAM) } , {"b", make_shared<Parameter>("b", TypeFactory::GetType("int"), INPUT_PARAM) } };
			ParamList outputs{ {"sum", make_shared<Parameter>("sum", Type("int"), OUTPUT_PARAM) }};

			InitializerType init = [](ParamList outputs) {
				outputs["sum"]->AllocateData(make_shared<Data<int>>(make_shared<int>(0)));
			};

			ComputerType computer = [](ParamList in, ParamList out) {
				(*static_pointer_cast<Data<int>>(out["sum"]->GetData())->Get()) = (*static_pointer_cast<Data<int>>(in["a"]->GetData())->Get()) + (*static_pointer_cast<Data<int>>(in["b"]->GetData())->Get());
			};
			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
	}
}


