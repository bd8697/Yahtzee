#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YahtzeeUnitTests
{
	TEST_CLASS(YahtzeeUnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		}
		TEST_METHOD(TestStringstream)
		{
			std::stringstream stream;
			stream << "Tests are working.";
			Assert::AreEqual(std::string("Tests are working."), stream.str(), L"If you see this message, the text is the same");
		}

		TEST_METHOD(ThisIsFalse)
		{
			std::stringstream stream;
			stream << "Hello.";
			Assert::AreEqual(std::string(" "), stream.str(), L"Hello");
		}
	};
}
