#pragma once
#include "Dice.h"
#include "ScoreTable.h"
#include <string>
#include <algorithm>
#include <vector>

class Player
{
public:
    explicit Player(std::string player);
	Player();
    const std::string GetName() const;
	void SetName(std::string player);

	~Player();
	void DisplayScoreOptions();
	void Roll();
	void RollDice();

	//for unit testing
	const std::vector<std::pair<ScoreTable::ScoreCategory, int>> GetScoreCandidates() const;
    const std::array<int, 7> GetDiceCount()const ;
	ScoreTable& GetScoreTable();
	Dice& GetDice();
	void SetDiceCount(int die);

	void ScoreDice(); 
	const bool SheetComplete() const;
	int SumOfTotalDie();
	const int TotalScore();
	void PrintScore() const;
	const bool TurnIsOver();
	

	unsigned int CheckPlayerScoreOption();
	void DisplayScoreCandidates();

public:
	void queryOnes();
	void QueryCandidates();
    void queryDieFace(const ScoreTable::ScoreCategory& scoreCategory, const int nrVal);
	void queryThreeOfAKind();
	void queryFourOfAKind();
	void queryFullHouse();
	void querySmallStraight();
	void queryLargeStraight();
	void queryYahtzee();
	void queryChance();

	Dice playerHand;
	Player operator= (const Player&);

private:
	std::string playerName;

	using categoryContainer = std::vector<std::pair<ScoreTable::ScoreCategory, int>>;
	categoryContainer scoreCandidates;
	std::array<int, 7> diceCount = { 0 };
	
	ScoreTable score;
	
	int currentTurn=0;


private:
	void DiceCount();
	void DeleteDiceCount();
	const int NumberOfDieRoll(int diceNumber) const;
	
};


