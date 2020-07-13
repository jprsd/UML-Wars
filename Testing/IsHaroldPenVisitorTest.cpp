#include "pch.h"
#include "CppUnitTest.h"
#include "IsHaroldPenVisitor.h"
#include "HaroldPen.h"
#include "PowerItem.h"
#include "PowerAllGone.h"
#include "Vector.h"
#include "Game.h"
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const wstring PowerItemImageName = L"poweritem/SlowFall.png";

namespace Testing
{
	TEST_CLASS(IsHaroldPenVisitorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(ConstructorTest)
		{
			CGame game;
			CVector position(0.0f, 0.0f);
			CVector velocity(0.0f, 0.0f);
			CHaroldPen hPen(position, velocity, &game);
			CIsHaroldPenVisitor visitor;
		}

		TEST_METHOD(TestPositiveAndNegative)
		{
			CGame game;
			CVector position(0.0f, 0.0f);
			CVector velocity(0.0f, 0.0f);
			CHaroldPen hPen(position, velocity, &game);
			CPowerAllGone pItem(position, velocity, &game);
			CIsHaroldPenVisitor visitor1;
			CIsHaroldPenVisitor visitor2;

			Assert::IsFalse(visitor1.IsHaroldPen(), L"Testing initialized visitor state");

			visitor1.VisitHaroldPen(&hPen);
			Assert::IsTrue(visitor1.IsHaroldPen(), L"Visited Item should be a HaroldPen");

			pItem.Accept(&visitor2);
			Assert::IsFalse(visitor2.IsHaroldPen(), L"Testing accept with wrong type");

			hPen.Accept(&visitor2);
			Assert::IsTrue(visitor2.IsHaroldPen(), L"Testing accept with HaroldPen");

		}
	};
}