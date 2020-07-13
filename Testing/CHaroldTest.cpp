/**
 * \file CHaroldTest.cpp
 *
 * \author Isaac Mayers
 */

#include "pch.h"
#include "CppUnitTest.h"
#include "Harold.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(HaroldTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestHaroldConstructor)
		{
			CHarold harold;
		}
		TEST_METHOD(TestHaroldSettersandGetters)
		{
			// testing getters and setters
			CHarold harold;
			double x = 10;
			double y = 15;
			harold.SetLocation(x,y);
			harold.SetAngle(45);
			Assert::IsTrue(harold.GetX() == 10 && harold.GetY() == 15, L"Testing location at 2, 3");
			Assert::IsTrue(harold.GetAngle() == 45, L"Testing angle at 10.3, 20.5");
		}

	};
}