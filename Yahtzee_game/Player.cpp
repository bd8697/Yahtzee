#include <utility>
#include "Player.h"
#include <vector>

Player::Player(std::string player) : playerName(std::move(player))
{
}

Player::Player()
{
	playerName = "default";
}

const std::string Player::GetName() const
{
	return playerName;
}

void Player::SetName(std::string player)
{
	playerName = player;
}

void Player::PrintScore() const
{
	//score.Print();
}


Player::~Player() = default;

void Player::DisplayScoreOptions()
{
	std::cout << "Candidates: \n";
	for (auto candidate : scoreCandidates)
	{
		std::cout << candidate.first << " | " << candidate.second;
		std::cout << std::endl;
	}
}

void Player::SetDiceCount(int die)
{
	diceCount[die]++;
}

void Player::RollDice()
{
	playerHand.DiceRoll();
}

void Player::Roll()
{
	DeleteDiceCount();
	score.ResetScore();
	DiceCount();
	//playerHand.Print();
	//std::cout << std::endl;
	currentTurn++;
}

const std::vector<std::pair<ScoreTable::ScoreCategory, int>> Player::GetScoreCandidates() const
{
	return scoreCandidates;
}
const std::array<int, 7> Player::GetDiceCount() const
{
	return diceCount;
}

ScoreTable& Player::GetScoreTable()
{
	return score;
}

Dice& Player::GetDice()
{
	return playerHand;
}

void Player::DisplayScoreCandidates()
{
	for (unsigned int index = 0; index < scoreCandidates.size(); index++)
	{
		std::cout << index + 1 << ". " << scoreCandidates.at(index).first << " -> points: " << scoreCandidates.at(index).second << std::endl;
	}
}
unsigned int Player::CheckPlayerScoreOption()
{
	unsigned int scoreCategory;
	std::cin >> scoreCategory;
	if (std::cin.fail())
		throw std::runtime_error("Input is not a number. Try again!");
	if (scoreCategory >= scoreCandidates.size() || scoreCategory <= 0)
		throw std::out_of_range("You entered an invalid option. Stick to those given! ");
	return scoreCategory;
}
void Player::ScoreDice()
{
	int playerOption = 0;
	if (!scoreCandidates.empty())
	{
		DisplayScoreCandidates();
		std::cout << "Please enter the category you'd like to score in: ";
		unsigned int scoreCategory;
		while (true)
		{
			try {
				scoreCategory = CheckPlayerScoreOption();
				break;
			}
			catch (std::exception & exp)
			{
				std::cout << exp.what() << "\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}
		playerOption = scoreCategory - 1;
		score.SetScore(scoreCandidates.at(playerOption).first, scoreCandidates.at(playerOption).second);

	}
	else
	{
		const signed int zeroScored = -1;

		for (int index = 0; index < ScoreTable::noOfCategories; index++)
		{
			auto currentCategory = static_cast<ScoreTable::ScoreCategory>(index);

			if (!score.isScored(currentCategory))
				scoreCandidates.push_back({ currentCategory, zeroScored });
		}

		DisplayScoreCandidates();
		std::cout << "Please select a category in which to place zero (0) points: ";
		unsigned int scoreCategory;
		while (true)
		{
			try {
				scoreCategory = CheckPlayerScoreOption();
				break;
			}
			catch (std::exception & exp)
			{
				std::cout << exp.what() << "\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}
		playerOption = scoreCategory - 1;
		score.SetScore(scoreCandidates.at(playerOption).first, scoreCandidates.at(playerOption).second);
	}
}

const bool Player::SheetComplete() const
{
	return score.IsFullScoreTable();
}

const int Player::TotalScore()
{
	return score.TotalScore();
}

const bool Player::TurnIsOver()
{
	if (currentTurn == 3)
	{
		playerHand.ReleaseAllDice();
		currentTurn = 0;
		return true;
	}
	else
	{
		int option;
		while (true)
		{
			try {
				std::cout << "Please enter the index of the die you'd like to hold (1 - 5), -1 to re-roll or 0 to end your turn: ";
				std::cin >> option;
				if (std::cin.fail())
					throw std::runtime_error("Input is not a number. Try again!");
				if (option >= 6 && option <= -2)
					throw std::out_of_range("You entered an invalid option. Stick to those given! ");
				break;
			}
		catch (std::exception & exp)
		{
			std::cout << exp.what() << "\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

		while (option != -1)
		{
			if (option == 0)
			{
				playerHand.ReleaseAllDice();
				currentTurn = 0;
				return true;
			}
			const int index = 1;

			playerHand.ToggleDice(option - index);
			playerHand.Print();
			std::cout << "Please enter the index of the die you'd like to hold (1 - 5), or -1 to re-roll or 0 to end your turn: ";
			while (true)
			{
				try {
			std::cin >> option;
			if (std::cin.fail())
				throw std::runtime_error("Input is not a number. Try again!");
			if (option >= 6 || option <= -2)
				throw std::out_of_range("You entered an invalid option. Stick to those given! ");
			break;
				}
				catch (std::exception & exp)
				{
					std::cout << exp.what() << "\n";
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cin >> option;

				}
			}
		}
		return false;
	}
}



Player Player::operator=(const Player& player)
{
	return player;
}

void Player::DiceCount()
{
	for (const auto& dice : playerHand.GetDiceArray())
	{
	    diceCount[dice->GetFace()]++;
	}
}

void Player::DeleteDiceCount()
{
	for (auto& dice : diceCount)
		dice = 0;
}

const int Player::NumberOfDieRoll(const int diceNumber) const
{
	return diceCount.at(diceNumber);
}

int Player::SumOfTotalDie()
{
	int totalScore = 0;
	for (int dice = 0; dice < diceCount.size(); dice++)
		totalScore += diceCount.at(dice)*dice;
	return totalScore;
}

void Player::QueryCandidates()
{
	scoreCandidates.clear();
    queryDieFace(ScoreTable::ScoreCategory::ONES, 1);
    queryDieFace(ScoreTable::ScoreCategory::TWOS, 2);
    queryDieFace(ScoreTable::ScoreCategory::THREES, 3);
    queryDieFace(ScoreTable::ScoreCategory::FOURS, 4);
    queryDieFace(ScoreTable::ScoreCategory::FIVES, 5);
    queryDieFace(ScoreTable::ScoreCategory::SIXES, 6);
	queryThreeOfAKind();
	queryFourOfAKind();
	queryFullHouse(); 
	querySmallStraight();
	queryLargeStraight();
	queryYahtzee();
	queryChance();
}

void Player::queryDieFace(const ScoreTable::ScoreCategory& scoreCategory, const int nrVal)
{
    bool isNotScored = !score.isScored(scoreCategory);
    int numberOfDieRoll = NumberOfDieRoll(nrVal);
    if (numberOfDieRoll != 0 && isNotScored)
    {
        score.SetScore(scoreCategory, -numberOfDieRoll * nrVal);
    }
}

void Player::queryThreeOfAKind()
{
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::THREE_OF_A_KIND) };

	for (unsigned int dice = 0; dice < diceCount.size(); dice++)
	{
		if (NumberOfDieRoll(dice) >= 3 && isNotScored)
		{
			score.SetScore(ScoreTable::ScoreCategory::THREE_OF_A_KIND, -SumOfTotalDie());
		}
	}
}

void Player::queryFourOfAKind()
{
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::FOUR_OF_A_KIND) };

	for (unsigned int dice = 0; dice < diceCount.size(); dice++)
	{
		if (NumberOfDieRoll(dice) >= 4 && isNotScored)
		{
			score.SetScore(ScoreTable::ScoreCategory::FOUR_OF_A_KIND, -SumOfTotalDie());
		}
	}
}

void Player::queryFullHouse()
{
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::FULLHOUSE) };
	bool twoOfAKind{ false };
	unsigned int dieOfFirstKind = 0;
	bool threeOfAnotherKind{ false };

	for (unsigned int die = 0; die < diceCount.size(); die++)
	{
		if (NumberOfDieRoll(die) == 2 && !twoOfAKind)
		{
			twoOfAKind = true;
			dieOfFirstKind = die;
		}

		if (NumberOfDieRoll(die) == 3 && dieOfFirstKind != die)
		{
			threeOfAnotherKind = true;
		}
	}

	if (isNotScored)
	{
		if (twoOfAKind && threeOfAnotherKind)
		{
			score.SetScore(ScoreTable::ScoreCategory::FULLHOUSE, -25);
		}
	}
}

void Player::querySmallStraight()
{
	std::vector<unsigned int> auxiliaryDice{};
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::SMALL_STRAIGHT) };

	for (const auto& dieOfHand : playerHand.GetDiceArray())
	{
		auxiliaryDice.push_back(dieOfHand->GetFace());
	}

	std::sort(auxiliaryDice.begin(), auxiliaryDice.end());
	std::unique(auxiliaryDice.begin(), auxiliaryDice.end());

	if (isNotScored)
	{
		if
			(
				(auxiliaryDice[0] == 1 && auxiliaryDice[1] == 2 && auxiliaryDice[2] == 3 && auxiliaryDice[3] == 4)
				||
				(auxiliaryDice[0] == 2 && auxiliaryDice[1] == 3 && auxiliaryDice[2] == 4 && auxiliaryDice[3] == 5)
				||
				(auxiliaryDice[0] == 3 && auxiliaryDice[1] == 4 && auxiliaryDice[2] == 5 && auxiliaryDice[3] == 6)
				||
				(auxiliaryDice[1] == 3 && auxiliaryDice[2] == 4 && auxiliaryDice[3] == 5 && auxiliaryDice[4] == 6)
			)
		{
			score.SetScore(ScoreTable::ScoreCategory::SMALL_STRAIGHT, -30);
		}
	 }
}

void Player::queryLargeStraight()
{
	std::vector<unsigned int> auxiliaryDice{};
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::BIG_STRAIGHT) };

	for (const auto& dieOfHand : playerHand.GetDiceArray())
	{
		auxiliaryDice.push_back(dieOfHand->GetFace());
	}

	std::sort(auxiliaryDice.begin(), auxiliaryDice.end());
	std::unique(auxiliaryDice.begin(), auxiliaryDice.end());


	if (isNotScored)
	{
		if
			(
				(auxiliaryDice[0] == 1 && auxiliaryDice[1] == 2 && auxiliaryDice[2] == 3 && auxiliaryDice[3] == 4 && auxiliaryDice[4] == 5)
				||
				(auxiliaryDice[0] == 2 && auxiliaryDice[1] == 3 && auxiliaryDice[2] == 4 && auxiliaryDice[3] == 5 && auxiliaryDice[4] == 6)
			)
		{
			score.SetScore(ScoreTable::ScoreCategory::BIG_STRAIGHT, -40);
		}
	}
}

void Player::queryYahtzee()
{
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::YAHTZEE) };

	for (unsigned int dice = 0; dice < diceCount.size(); dice++)
	{
		if (NumberOfDieRoll(dice) == 5)
		{
			if (isNotScored) {
				score.SetScore(ScoreTable::ScoreCategory::YAHTZEE, -50);
			}
			else {
				static uint8_t yahtzeeCounter = 1;
				score.SetScore(ScoreTable::ScoreCategory::YAHTZEE, -(50 + 100 * yahtzeeCounter++));
			}
		}
	}
}

void Player::queryChance()
{
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::CHANCE) };

	if (isNotScored)
	{
		score.SetScore(ScoreTable::ScoreCategory::CHANCE, -SumOfTotalDie());
	}
}

void Player::queryOnes()
{
	int ones{ 1 };
	bool isNotScored{ !score.isScored(ScoreTable::ScoreCategory::ONES) };

	if (NumberOfDieRoll(ones) != 0 && isNotScored)
	{
		scoreCandidates.push_back(std::make_pair( ScoreTable::ScoreCategory::ONES, NumberOfDieRoll(ones) * ones ));
	}
}
