#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "Parameter.h"
#include "Node.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpenCVGraphTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ParameterIsCompatible)
		{
			std::shared_ptr<Parameter> p1 = std::make_shared<Parameter>("test1", Type("int"), INPUT_PARAM);
			std::shared_ptr<Parameter> p2 = std::make_shared<Parameter>("test2", Type("int"), INPUT_PARAM); // Fail
			std::shared_ptr<Parameter> p3 = std::make_shared<Parameter>("test3", Type("string"), INPUT_PARAM); // Fail
			std::shared_ptr<Parameter> p4 = std::make_shared<Parameter>("test4", Type("string"), OUTPUT_PARAM); // Fail
			std::shared_ptr<Parameter> p5 = std::make_shared<Parameter>("test5", Type("int"), OUTPUT_PARAM); // Succeed
			std::shared_ptr<Parameter> p6 = std::make_shared<Parameter>("test6", Type("int"), OUTPUT_PARAM); // Fail because same parents

			p1->SetParent(std::make_shared<Node>().get());
			p2->SetParent(std::make_shared<Node>().get());
			p3->SetParent(std::make_shared<Node>().get());
			p4->SetParent(std::make_shared<Node>().get());
			p5->SetParent(std::make_shared<Node>().get());
			p6->SetParent(p1->GetParent());

			Assert::IsTrue(!p1->IsCompatible(p2), L"Two inputs with same type can't link");
			Assert::IsTrue(!p1->IsCompatible(p3), L"Two inputs with different types can't link");
			Assert::IsTrue(!p1->IsCompatible(p4), L"Input with output with different types can't link");
			Assert::IsTrue(p1->IsCompatible(p5), L"Input with output with same types can link");
			Assert::IsTrue(!p1->IsCompatible(p6), L"Input with output with same types but same parent can't link");
		}

	};
}