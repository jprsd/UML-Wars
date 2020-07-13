#include "pch.h"
#include "CppUnitTest.h"
#include "ScoreBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CScoreBoardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructor)
		{
			CScoreBoard scoreBoard;
		}

		TEST_METHOD(TestIncrementAndGetterFunctions)
		{
			CScoreBoard scoreBoard;

			Assert::AreEqual(0, scoreBoard.GetCorrect(), L"Correct hits score");
			scoreBoard.IncrementCorrect();
			Assert::AreEqual(1, scoreBoard.GetCorrect(), L"Correct hits incremented score");
			
			Assert::AreEqual(0, scoreBoard.GetMissed(), L"Missed score");
			scoreBoard.IncrementMissed();
			Assert::AreEqual(1, scoreBoard.GetMissed(), L"Missed incremented score");

			Assert::AreEqual(0, scoreBoard.GetUnfair(), L"Unfair hits score");
			scoreBoard.IncrementUnfair();
			Assert::AreEqual(1, scoreBoard.GetUnfair(), L"Unfair hits incremented score");
		}

	};
}