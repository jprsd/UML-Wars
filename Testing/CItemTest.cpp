#include "pch.h"
#include "CppUnitTest.h"
#include "Item.h"
#include "Game.h"
#include "Vector.h"
#include "HaroldPen.h"
#include <string>

using namespace Gdiplus;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/// Pen filename 
const wstring PenImageName = L"images/redpen.png";

/** Mock class for testing CItem */
class CItemMock : public CItem
{
public:
	CItemMock(CVector position, CVector velocity, CGame* game) : 
		CItem(position, velocity, game) {}

	virtual void Draw(Gdiplus::Graphics* graphics, CVector position) override {}

	virtual void Accept(CItemVisitor* visitor) override {}

	virtual void Effect() override {}

	virtual CVector GetDimensions() const { return CVector(); }

};


namespace Testing
{
	TEST_CLASS(ItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestItemConstructor)
		{
			CGame game;
			CVector position(0.0f, 0.0f);
			CVector velocity(0.0f, 0.0f);
			CItemMock item(position, velocity, &game);
		}

		TEST_METHOD(TestCItemGettersSetters)
		{
			// Construct an item to test
			CGame game;
			CItemMock item(CVector(0,0), CVector(0,0), &game);

			// Test initial values
			Assert::AreEqual(0, item.GetPosition().X(), 0);
			Assert::AreEqual(0, item.GetPosition().Y(), 0);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(CVector(10.5, 17.2));
			Assert::AreEqual(10.5, item.GetPosition().X(), 0.0001);
			Assert::AreEqual(17.2, item.GetPosition().Y(), 0.0001);

			// Test a second with different values
			item.SetLocation(CVector(-72, -107));
			Assert::AreEqual(-72, item.GetPosition().X(), 0.0001);
			Assert::AreEqual(-107, item.GetPosition().Y(), 0.0001);
		}

	};
}