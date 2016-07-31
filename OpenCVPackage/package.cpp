#include <map>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "../OpenCVGraph/src/Node.h"
#include "../OpenCVGraph/src/Parameter.h"
#include "../OpenCVGraph/src/Data.h"

using namespace std;
using namespace cv;

extern "C"
{
	__declspec(dllexport) void GetNodesNames(vector<string>& names) {
		names = { "imread", "VideoCapture", "Gaussian blur", "Canny" };
	}
	__declspec(dllexport) void NodeFactory(string name, shared_ptr<Node>& node) {
		if (name == "imread") {
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
		else if (name == "VideoCapture") {
			ParamList inputs{};
			ParamList outputs{ { "value", make_shared<Parameter>("value", TypeFactory::GetType("Mat"), OUTPUT_PARAM) },
			{ "cap", make_shared<Parameter>("cap", TypeFactory::GetType("VideoCapture"), OUTPUT_PARAM) } };

			InitializerType init = [](ParamList outputs) {
				// Create the variable
				outputs["value"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				outputs["cap"]->AllocateData(make_shared<Data<VideoCapture>>(make_shared<VideoCapture>(0)));
				(*static_pointer_cast<Data<VideoCapture>>(outputs["cap"]->GetData())->Get()).set(CV_CAP_PROP_FRAME_WIDTH, 1280);
				(*static_pointer_cast<Data<VideoCapture>>(outputs["cap"]->GetData())->Get()).set(CV_CAP_PROP_FRAME_HEIGHT, 720);
				// Put an image in it
				(*static_pointer_cast<Data<Mat>>(outputs["value"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);
		

			};

			ComputerType computer = [](ParamList in, ParamList out) {
				Mat& value = (*static_pointer_cast<Data<Mat>>(out["value"]->GetData())->Get().get());
				VideoCapture cap((*static_pointer_cast<Data<VideoCapture>>(out["cap"]->GetData())->Get().get()));

				 // open the default camera
				if (!cap.isOpened())  // check if we succeeded
					return;

				Mat tmp;
				cap >> tmp; // get a new frame from camera
				// Copy the data as by default OpenCV performs a soft-copy
				tmp.copyTo(value);
			};

			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
		else if (name == "Gaussian blur") {
			ParamList inputs{ {"src", make_shared<Parameter>("src", TypeFactory::GetType("Mat"), INPUT_PARAM) },
			{ "kernelSize", make_shared<Parameter>("kernelSize", TypeFactory::GetType("int"), INPUT_PARAM) } };
			ParamList outputs{ {"dst", make_shared<Parameter>("dst", TypeFactory::GetType("Mat"), OUTPUT_PARAM) }};

			InitializerType init = [](ParamList outputs) {
				outputs["dst"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				(*static_pointer_cast<Data<Mat>>(outputs["dst"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);

			};

			ComputerType computer = [](ParamList in, ParamList out) {
				Mat& src = (*static_pointer_cast<Data<Mat>>(in["src"]->GetData())->Get().get());
				int& kernelSize = (*static_pointer_cast<Data<int>>(in["kernelSize"]->GetData())->Get().get());
				Mat& dst = (*static_pointer_cast<Data<Mat>>(out["dst"]->GetData())->Get().get());
				// Gaussian blur only accepts odd numbers in kernel size
				if (kernelSize % 2 == 0)
					return;

				GaussianBlur(src, dst, Size(kernelSize, kernelSize), 0, 0);
			};
			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
		else if (name == "Canny") {
			ParamList inputs{ { "src", make_shared<Parameter>("src", TypeFactory::GetType("Mat"), INPUT_PARAM) },
			{ "lowThreshold", make_shared<Parameter>("lowThreshold", TypeFactory::GetType("int"), INPUT_PARAM) },
			{ "ratio", make_shared<Parameter>("ratio", TypeFactory::GetType("int"), INPUT_PARAM) },
			{ "kernelSize", make_shared<Parameter>("kernelSize", TypeFactory::GetType("int"), INPUT_PARAM) } };
			ParamList outputs{ { "dst", make_shared<Parameter>("dst", TypeFactory::GetType("Mat"), OUTPUT_PARAM) } };

			InitializerType init = [](ParamList outputs) {
				outputs["dst"]->AllocateData(make_shared<Data<Mat>>(make_shared<Mat>()));
				(*static_pointer_cast<Data<Mat>>(outputs["dst"]->GetData())->Get()) = imread("default.jpg", IMREAD_COLOR);

			};

			ComputerType computer = [](ParamList in, ParamList out) {
				Mat& src = (*static_pointer_cast<Data<Mat>>(in["src"]->GetData())->Get().get());
				int& lowThreshold = (*static_pointer_cast<Data<int>>(in["lowThreshold"]->GetData())->Get().get());
				int& ratio = (*static_pointer_cast<Data<int>>(in["ratio"]->GetData())->Get().get());
				int& kernelSize = (*static_pointer_cast<Data<int>>(in["kernelSize"]->GetData())->Get().get());
				Mat& dst = (*static_pointer_cast<Data<Mat>>(out["dst"]->GetData())->Get().get());
				// Gaussian blur only accepts odd numbers in kernel size (used by Canny)
				if (kernelSize % 2 == 0 || kernelSize < 3 || lowThreshold%2==0 || lowThreshold*ratio%2==0)
					return;

				Canny(src, dst, lowThreshold, lowThreshold*ratio, kernelSize);
			};
			node = make_shared<Node>(name, inputs, outputs, init, computer);
		}
	}
}


