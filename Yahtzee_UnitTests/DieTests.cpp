#include "pch.h"
#include "CppUnitTest.h"
#include "../Yahtzee_game/Die.h"
#include <array>
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YahtzeeUnitTests
{
	TEST_CLASS(DieTests)
	{
	public:

		TEST_METHOD(GetSameValueTwiceIfNotThrown)
		{
			Die dieOne;
			auto dieTwo = dieOne.GetFace();
			auto dieThree = dieOne.GetFace();
			Assert::AreEqual(dieTwo, dieThree);
		}
		TEST_METHOD(GetValueShouldReturnIntBetween1to6)
		{
			Die dieOne;
			auto value = dieOne.GetFace();
			Assert::IsFalse(value > 6 || value < 1);
		}
		TEST_METHOD(ShouldNotAcceptNull)
		{
			Die die;
			die.SetFace(NULL);
			Die dieTwo(die);
			if (dieTwo.GetFace() == NULL) Assert::Fail();
		}
		TEST_METHOD(CheckDisplayFaces)
		{
			Die die;
			die.SetDisplayFaces(8);
			if (die.GetFace()>8 && die.GetDisplayFaces()!=NULL ) Assert::Fail();
		}
	};
}
