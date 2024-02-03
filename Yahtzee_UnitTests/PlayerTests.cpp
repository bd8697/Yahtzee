#include "pch.h"
#include "CppUnitTest.h"
#include "../Yahtzee_game/Player.h"
#include<algorithm>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayerTests
{
	TEST_CLASS(PlayerTests)
	{
	public:
		TEST_METHOD(DefaultConstructorPlayer)
		{
			Player* player = new Player();
			Assert::IsTrue(player->GetName() == "default");

		}

		TEST_METHOD(SetGetPlayer)
		{
			Player player;
			player.SetName("Mr.Player");
			Assert::IsTrue(player.GetName() == "Mr.Player");
		}

		TEST_METHOD(SetTwoOnesThenQueryOnes)
		{
			Player player;
			std::vector<std::pair<ScoreTable::ScoreCategory, int>> scoreCandidates;
			int index = 0;
			while (index < 2)
			{
				player.SetDiceCount(1);
				index++;
			}
			scoreCandidates.push_back(std::make_pair(ScoreTable::ScoreCategory::ONES, 2 * 1));
			player.queryOnes();
			Assert::AreEqual(player.GetScoreCandidates().front().second, scoreCandidates.front().second);
		}

		TEST_METHOD(SetThreeOnesThenQueryOnes)
		{
			Player player;
			std::vector<std::pair<ScoreTable::ScoreCategory, int>> scoreCandidates;
			int index = 0;
			while (index < 3)
			{
				player.SetDiceCount(1);
				index++;
			}
			scoreCandidates.push_back(std::make_pair(ScoreTable::ScoreCategory::ONES, 3 * 1));
			player.queryOnes();
			Assert::AreEqual(player.GetScoreCandidates().front().second, scoreCandidates.front().second);
		}

		TEST_METHOD(SetFourOnesThenQueryOnes)
		{
			Player player;
			std::vector<std::pair<ScoreTable::ScoreCategory, int>> scoreCandidates;
			int index = 0;
			while (index < 4)
			{
				player.SetDiceCount(1);
				index++;
			}
			scoreCandidates.push_back(std::make_pair(ScoreTable::ScoreCategory::ONES, 4 * 1));
			player.queryOnes();
			Assert::AreEqual(player.GetScoreCandidates().front().second, scoreCandidates.front().second);
		}

		TEST_METHOD(SetFiveOnesThenQueryOnes)
		{
			Player player;
			std::vector<std::pair<ScoreTable::ScoreCategory, int>> scoreCandidates;
			int index = 0;
			while (index < 5)
			{
				player.SetDiceCount(1);
				index++;
			}
			scoreCandidates.push_back(std::make_pair(ScoreTable::ScoreCategory::ONES, 5 * 1));
			player.queryOnes();
			Assert::AreEqual(player.GetScoreCandidates().front().second, scoreCandidates.front().second);
		}
	};
}
