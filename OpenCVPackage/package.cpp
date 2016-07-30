#include <map>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "../OpenCVGraph/src/Node.h"
#include "../OpenCVGraph/src/Parameter.h"
#include "../OpenCVGraph/src/Data.h"

using namespace std;
using namespace cv;

extern "C"
{
	__declspec(dllexport) string* GetPackageName() {
		return new string("OpenCV");
	}
	__declspec(dllexport) void GetNodesNames(vector<string>& names) {
		names = { "Mat", "Gaussian blur" };
	}
	__declspec(dllexport) void NodeFactory(string name, shared_ptr<Node>& node) {
		if (name == "Mat") {
			string name = "Mat";
			ParamList inputs{};
			ParamList outputs{ {"value", make_shared<Parameter>("value", TypeFactory::GetType("Mat"), OUTPUT_PARAM) } };

			InitializerType init = [](ParamList outputs) {
				// Create the variable
				outputs["value"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				// Put an image in it
				(*static_pointer_cast<Data<Mat>>(outputs["value"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);
			};

			ComputerType computer = [](ParamList in, ParamList out) {
			};

			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
		if (name == "Gaussian blur") {
			string name = "Gaussian blur";
			ParamList inputs{ {"src", make_shared<Parameter>("src", TypeFactory::GetType("Mat"), INPUT_PARAM) },
			{ "kernelSize", make_shared<Parameter>("kernelSize", TypeFactory::GetType("int"), INPUT_PARAM) } };
			ParamList outputs{ {"dst", make_shared<Parameter>("dst", TypeFactory::GetType("Mat"), OUTPUT_PARAM) }};

			InitializerType init = [](ParamList outputs) {
				outputs["dst"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				(*static_pointer_cast<Data<Mat>>(outputs["dst"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);

			};

			ComputerType computer = [](ParamList in, ParamList out) {
				Mat src = (*static_pointer_cast<Data<Mat>>(in["src"]->GetData())->Get().get());
				int kernelSize = (*static_pointer_cast<Data<int>>(in["kernelSize"]->GetData())->Get().get());
				Mat dst = (*static_pointer_cast<Data<Mat>>(out["dst"]->GetData())->Get().get());
				// Gaussian blur only accepts odd numbers in kernel size
				if (kernelSize % 2 == 0)
					return;

				GaussianBlur(src, dst, Size(kernelSize, kernelSize), 0, 0);
			};
			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
	}
	__declspec(dllexport) void DeletePackageName(string* name) {
		delete name;
	}
}


