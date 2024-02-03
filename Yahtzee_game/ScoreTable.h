#pragma once
#include <string>
#include <map>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>

// Score table appears at the top of the console at all times.
class ScoreTable
{
public:
	enum class ScoreCategory { TOTAL = 0, ONES, TWOS, THREES, FOURS, FIVES, SIXES, THREE_OF_A_KIND, FOUR_OF_A_KIND, FULLHOUSE, SMALL_STRAIGHT, BIG_STRAIGHT, YAHTZEE, CHANCE};
	static const int noOfCategories = 14;
	const int categoryStringLength[noOfCategories] = { 4,4,6,5,5,5,15,14,9,14,12,8,6 }; // no static because I get an error

	ScoreTable();
	ScoreTable(std::string ownerOfTable);
	~ScoreTable();

	std::string GetOwner();
	int GetNoOfCategories();
    void ResetScore();

	std::map<ScoreCategory, int>& GetScore();
	void SetScore(const ScoreCategory& cat, int toScore);
	int GetScoreAt(const ScoreCategory& cat);
	bool IsFullScoreTable() const;
	int TotalScore();
	bool isScored(const ScoreCategory& cat);
	bool DrawTable(sf::RenderWindow& window, int x, const int& y, sf::Text text, const int& time, int rollsLeft);
	std::string EnumToString(ScoreTable::ScoreCategory cat);
	void DrawAnimation(sf::RenderWindow& window, const int& time, int x, const int& y);
	friend ScoreCategory& operator++(ScoreCategory& cat);
	friend std::ostream& operator<<(std::ostream& out, ScoreCategory cat);

	void Print(const int& consoleLength, const int& maxLengthFirstColumn, const int& maxLengthSecondColumn) const;

private:
	std::map<ScoreCategory, int> score;
    std::string owner;
	sf::Vector2i mousePos;
	sf::SoundBuffer soundBuffer;
	sf::Sound pick;
	float colorTimer = 200;
	int colorSwitch = 1;
};
