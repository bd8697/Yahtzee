#include "pch.h"
#include "CppUnitTest.h"
#include "../Yahtzee_game/ScoreTable.h"
#include <random>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ScoreTableTests
{
	TEST_CLASS(ScoreTableTests)
	{
	public:

		TEST_METHOD(CreateEmptyTable)
		{
			ScoreTable table;
			std::string defaultPlayer = "";
			Assert::AreEqual(table.GetOwner(), defaultPlayer);
			std::map<ScoreTable::ScoreCategory, int> score;
			score = table.GetScore();
			for (auto i = score.begin(); i != score.end(); i++)
			{
				if (i->second != -1)
				{
					Assert::Fail();
				}
			}
		}
		TEST_METHOD(ThisIsFalse)
		{
			std::stringstream stream;
			stream << "Hello.";
			Assert::AreEqual(std::string(" "), stream.str(), L"Hello");
		}

		TEST_METHOD(FullTable)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist10(1, 10); // distribution in range [1, 10]
			ScoreTable table;
			ScoreTable::ScoreCategory i = ScoreTable::ScoreCategory::ONES;
			table.SetScore(i, dist10(rng));
			do
			{
				++i;
				table.SetScore(i, dist10(rng));
			} while (i != ScoreTable::ScoreCategory::CHANCE);

			Assert::IsTrue(table.IsFullScoreTable());
		}

		TEST_METHOD(IsValidTotalScore)
		{
			ScoreTable table;
			ScoreTable::ScoreCategory i = ScoreTable::ScoreCategory::ONES;
			table.SetScore(i, 50);
			do
			{
				++i;
				table.SetScore(i, 10);
			} while (i != ScoreTable::ScoreCategory::CHANCE);
			Assert::AreEqual(table.TotalScore(), 50 + 5 * 10 + 7 * 10 + 35);
		}

		TEST_METHOD(ScoredCategory)
		{
			ScoreTable table;
			table.SetScore(ScoreTable::ScoreCategory::FULLHOUSE, 13);
			Assert::IsTrue(table.isScored(ScoreTable::ScoreCategory::FULLHOUSE));
		}

		TEST_METHOD(PrintCorrectCategory)
		{
			ScoreTable table;
			std::stringstream stream;
			stream << table.GetScore().begin()->first;
			Assert::AreEqual(std::string("Ones"), stream.str(), L"If you see this message, the category is not printed correctly.");
		}

		TEST_METHOD(PrintCorrectScoreAtCategory)
		{
			ScoreTable table;
			ScoreTable::ScoreCategory cat = ScoreTable::ScoreCategory::SIXES;
			table.SetScore(cat, 13);
			std::stringstream stream;
			stream << table.GetScoreAt(cat);
			Assert::AreEqual(std::string("13"), stream.str(), L"If you see this message, the score is not printed correctly.");
		}

		TEST_METHOD(IsCategoryInTable)
		{
			ScoreTable table;
			ScoreTable::ScoreCategory cat = ScoreTable::ScoreCategory::SIXES;
			std::map<ScoreTable::ScoreCategory, int> score;
			score = table.GetScore();
			std::map<ScoreTable::ScoreCategory, int>::iterator it;

			it = score.find(cat);
			if (it == score.end())
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(NoOfCategoriesInTable)
		{
			ScoreTable table;
			std::map<ScoreTable::ScoreCategory, int> score;
			score = table.GetScore();

			int dist = 0;
			dist = std::distance(score.begin(), score.end());

			Assert::AreEqual(13, dist);
			//also use dist in ScoreTable.h declaration. Maybe.
		}
	};
}
