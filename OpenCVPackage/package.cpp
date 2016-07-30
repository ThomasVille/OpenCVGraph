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
		names = { "Mat", "ConvertToGrey" };
	}
	__declspec(dllexport) Data<Node>* CreateNode(string name) {
		if (name == "Mat") {
			string name = "Mat";
			ParamList inputs{};
			ParamList outputs{ {"value", make_shared<Parameter>("value", Type("Mat"), OUTPUT_PARAM) } };

			InitializerType init = [](ParamList outputs) {
				// Create the variable
				outputs["value"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				// Put an image in it
				(*static_pointer_cast<Data<Mat>>(outputs["value"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);
			};

			ComputerType computer = [](ParamList in, ParamList out) {
				//(*static_pointer_cast<Data<int>>(out["value"]->GetData())->Get()) = 42;
			};

			return new Data<Node>(make_shared<Node>(name, inputs, outputs, init, computer));
		}
		if (name == "ConvertToGrey") {
			string name = "ConvertToGrey";
			ParamList inputs{ {"src", make_shared<Parameter>("src", Type("Mat"), INPUT_PARAM) } };
			ParamList outputs{ {"dst", make_shared<Parameter>("dst", Type("Mat"), OUTPUT_PARAM) }};

			InitializerType init = [](ParamList outputs) {
				outputs["dst"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				(*static_pointer_cast<Data<Mat>>(outputs["dst"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);

			};

			ComputerType computer = [](ParamList in, ParamList out) {
				Mat src = (*static_pointer_cast<Data<Mat>>(in["src"]->GetData())->Get().get());
				Mat dst = (*static_pointer_cast<Data<Mat>>(out["dst"]->GetData())->Get().get());
				src.convertTo(dst, -1, 2.0);
			};
			return new Data<Node>(make_shared<Node>(name, inputs, outputs, init, computer));
		}
		return nullptr;
	}
	__declspec(dllexport) void DeletePackageName(string* name) {
		delete name;
	}
	__declspec(dllexport) void DeleteNode(Data<Node>* node) {
		delete node;
	}
}


