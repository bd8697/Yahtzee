#include "ScoreTable.h"
#include <string>
#include <iostream>
#include <cmath>
#include <SFML\Graphics\RectangleShape.hpp>
#include "MySprite.h"
#include "Console.h"

ScoreTable::ScoreTable() : score()
{
	for (int i = 0; i < GetNoOfCategories(); i++)
		score[ScoreCategory(i)] = -1;

	soundBuffer.loadFromFile("../assetz/pencil.wav");
	pick.setBuffer(soundBuffer);
}

ScoreTable::ScoreTable(std::string theOwner)
	:score(), owner(std::move(theOwner))
{
	for (int i = 0; i < GetNoOfCategories(); i++)
		score[ScoreCategory(i)] = -1;
}

ScoreTable::~ScoreTable() = default;

std::string ScoreTable::GetOwner() {
	return owner;
}

void ScoreTable::SetScore(const ScoreCategory& cat, int toScore)
{
	score[cat] = toScore;
}

bool ScoreTable::IsFullScoreTable() const
{
	bool isFull = true;

	for (auto i : score)
		if (i.second < 0)
			isFull = false;

	return isFull;
}

int ScoreTable::TotalScore()
{
	int firstHalf = 0;
	int secondHalf = 0;

	for (ScoreCategory i = ScoreCategory::ONES; i != ScoreCategory::THREE_OF_A_KIND; ++i)
		if (score[i] > -1)
			firstHalf += score[i];

	if (firstHalf >= 63) // rules
		firstHalf += 35;

	for (ScoreCategory i = ScoreCategory::THREE_OF_A_KIND; i != ScoreCategory::TOTAL; ++i)
		if (score[i] > -1)
			secondHalf += score[i];

	int total = firstHalf + secondHalf;

	return total;
}

bool ScoreTable::isScored(const ScoreCategory& cat)
{
	return score[cat] != -1;
}

void ScoreTable::Print(const int& consoleLength, const int& maxLengthFirstColumn, const int& maxLengthSecondColumn) const
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2); // set text color to second arg
	int drawAtPos = (consoleLength / 2 - (maxLengthFirstColumn + maxLengthSecondColumn + 1) / 2);
	int count = 0;
	std::string tableName = "$$$ Score Table $$$";
	// $printing header
	for (int i = 0; i < drawAtPos; i++) {
		std::cout << ' ';
	}
	std::cout << '+';
	for (int i = 0; i < maxLengthFirstColumn + maxLengthSecondColumn + 1; i++)
	{
		std::cout << '-';
	}
	std::cout << '+' << std::endl;
	for (int i = 0; i < drawAtPos; i++) {
		std::cout << ' ';
	}
	std::cout << '|';
	for (int i = 0; i < (signed int)(maxLengthFirstColumn + maxLengthSecondColumn + 1 - tableName.size()) / 2; i++)
	{
		std::cout << ' ';
	}
	
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << tableName;
	SetConsoleTextAttribute(hConsole, 2);
	for (int i = 0; i < (signed int)(maxLengthFirstColumn + maxLengthSecondColumn + 1 - tableName.size()) / 2; i++)
	{
		std::cout << ' ';
	}
	std::cout << '|' << std::endl;

	 //printing rest of table
	 for (auto i = score.begin(); i != score.end(); i++) 
	 {
	 	for (int i = 0; i < drawAtPos; i++) {
	 		std::cout << ' ';
	 	}
	 	std::cout << '+';
	 	for (int i = 0; i < maxLengthFirstColumn; i++)
	 	{
	 		std::cout << '-';
	 	}
	 	std::cout << '+';
	 	for (int i = 0; i < maxLengthSecondColumn; i++)
	 	{
	 		std::cout << '-';
	 	}
	 	std::cout << '+'<<std::endl;
	 	for (int i = 0; i < drawAtPos; i++) {
	 		std::cout << ' ';
	 	}
	 	std::cout << '|';
	 	SetConsoleTextAttribute(hConsole, 14);
	 	std::cout<<i->first;
	 	SetConsoleTextAttribute(hConsole, 2);
	 	for (int j = 0; j < maxLengthFirstColumn - categoryStringLength[count]; j++)
	 		std::cout << ' ';
	 	std::cout << '|';
	 	SetConsoleTextAttribute(hConsole, 4);
	 	std::cout<< i->second;
	 	SetConsoleTextAttribute(hConsole, 2);
	 	for (int j = 0; j <maxLengthSecondColumn - std::to_string(i->second).size(); j++)
	 		std::cout << ' ';
	 	std::cout << '|' << std::endl;
	 	count++;
	 }

	for (int i = 0; i < drawAtPos; i++) {
		std::cout << ' ';
	}
	std::cout << '+';
	for (int i = 0; i < maxLengthFirstColumn; i++)
	{
		std::cout << '-';
	}
	std::cout << '+';
	for (int i = 0; i < maxLengthSecondColumn; i++)
	{
		std::cout << '-';
	}
	std::cout << '+';
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	// std::cout << i->first << ": " << i->second << std::endl; // ->first returns the key; ->second returns the value
}

std::map<ScoreTable::ScoreCategory, int>& ScoreTable::GetScore() {
	return score;
}

bool ScoreTable::DrawTable(sf::RenderWindow& window, int x, const int& y, sf::Text text, const int& time, int rollsLeft)
{
	bool scored = false;
    // Show suggestion best score
    auto maxScore = std::min_element( score.begin(), score.end(),
                                 []( const std::pair<ScoreCategory, int> &a, const std::pair<ScoreCategory, int> &b )
                                 {
                                     return a.second < b.second;
                                 } );
    if (maxScore->second < -1) {
        std::string suggestion = "Suggestion: keep " + EnumToString(maxScore->first);
        if (rollsLeft > 0
            && maxScore->first != ScoreCategory::FULLHOUSE
            && maxScore->first != ScoreCategory::YAHTZEE
            && maxScore->first != ScoreCategory::CHANCE) {
            suggestion +=  " and roll the other dice";
        }
        text.setString(suggestion);
        text.setFillColor(sf::Color(252, 247, 94));
        text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2, window.getSize().y - 30.0);
        window.draw(text);
    }

	text.setString("    $$$  SCORE TABLE  $$$    "); // how we want the longest row to look like
	int maxSize = text.getLocalBounds().width; // take this outside of the function body, where you call it
	int characterSize = text.getCharacterSize();
	int count = 1;
	sf::RectangleShape rectangle;
	mousePos = sf::Mouse::getPosition(window);

	//DrawAnimation(window, time, x + window.getSize().x - (2 * text.getLocalBounds().width), y + text.getCharacterSize() * 7);

    for (auto i = score.begin(); i != score.end(); i++)
	{
		if (count == 1)
		{
			rectangle.setFillColor(sf::Color(0, 16, 4));
			rectangle.setPosition(x, y); // where we start drawing the table
			rectangle.setSize(sf::Vector2f(maxSize, characterSize * 2));
			window.draw(rectangle);
			text.setString("    $$$  SCORE TABLE  $$$    ");
			text.setFillColor(sf::Color(252, 247, 94));
			text.setPosition(x, y);
			window.draw(text);
		}

		rectangle.setPosition(x, y + characterSize * 2 * count);
		rectangle.setSize(sf::Vector2f(maxSize + 1 * characterSize / 2, characterSize / 2));
		window.draw(rectangle);
		text.setFillColor(sf::Color(252, 247, 94));
		text.setString(EnumToString(i->first));
		text.setPosition(x + characterSize, y + characterSize * 2 * count + characterSize / 2);
		window.draw(text);
		if (i->second < -1)
		{
			if (colorTimer >= 255 || colorTimer <= 0)
			{
				colorSwitch *= -1;
			}
			colorTimer += 1 * colorSwitch;
			// std::cout << colorTimer << std::endl;
			text.setFillColor(sf::Color(252, colorTimer, 94)); // colorTimer as first argument for green, second for pink, third for white
		}
		else
		{
			text.setFillColor(sf::Color(252, 247, 94));
		}
		if (i->second == -1)
		{
			text.setString("X");
			text.setFillColor(sf::Color(255, 36, 0));
		}
		else
		{
			text.setString(std::to_string(abs(i->second)));
		}

		int len = ((std::string)text.getString()).length();
		text.setPosition(x + maxSize * 3 / 4 + 2 * characterSize - characterSize / 4 * len, y + characterSize * 2 * count + characterSize / 2);
		
		if (i->second <= -1 && rollsLeft < 3)
		{
			if (mousePos.y > (y + characterSize * 2 * count + characterSize / 2) && mousePos.y < ((y + characterSize * 2 * count + characterSize / 2) + characterSize))
			{
				if (mousePos.x > (x + maxSize * 3 / 4 + 2 * characterSize - characterSize / 4 * len) && mousePos.x < (x + maxSize * 3 / 4 + 2 * characterSize - characterSize / 4 * len) + characterSize * len)
				{
					if (i->second == -1)
					{
						text.setString("0");
					}
					text.setFillColor(sf::Color(252, 247, 94));

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						scored = true;
						
						pick.play();
						if (i->second == -1)
						{
							i->second = 0;
						}
						else
						{
							i->second = abs(i->second);
						}
						score.begin()->second = TotalScore();
						// std::cout << TotalScore() << "    " << score.begin()->second << std::endl;
						ResetScore();
					}
				}
			}
		}
		window.draw(text);
		count++;

		if (count == ceil((float)score.size() / 2) + 1 || EnumToString(i->first) == "CHANCE") // will add "total" category to scoretable
		{
			rectangle.setPosition(x, y + characterSize * 2 * count);
			window.draw(rectangle);
			rectangle.setSize(sf::Vector2f(characterSize / 2, characterSize * 2 * (count)));
			rectangle.setPosition(x, y);
			window.draw(rectangle);
			rectangle.setPosition(x + maxSize * 3 / 4, y);
			window.draw(rectangle);
			rectangle.setPosition(x + maxSize, y);
			window.draw(rectangle);
			x = window.getSize().x - maxSize - x; // maxSize * scale to be dynamic on window resize
			count = 1;
		}

	}
	switch (scored)
	{
	case true: return true; break;
	case false: return false;
	}
}

void ScoreTable::DrawAnimation(sf::RenderWindow& window, const int& time, int x, const int& y) {
	int count = 0;
	if (count == 5) // reset animation
	{
		count = 0;
	}
	if (time % 2 == 0) // changes every 2 seconds, really slow
	{
		count++;
	}
}

int ScoreTable::GetNoOfCategories() {
	return noOfCategories;
}

void ScoreTable::ResetScore() {
    for (auto & i : score)
    {
        if (i.second < -1)
        {
            i.second = -1;
        }
    }
}

int ScoreTable::GetScoreAt(const ScoreCategory& cat)
{
	return score[cat];
}

ScoreTable::ScoreCategory& operator++(ScoreTable::ScoreCategory& cat)
{
	switch (cat)
	{
	case ScoreTable::ScoreCategory::TOTAL:
		cat = ScoreTable::ScoreCategory::ONES;
		break;
	case ScoreTable::ScoreCategory::ONES:
		cat = ScoreTable::ScoreCategory::TWOS;
		break;
	case ScoreTable::ScoreCategory::TWOS:
		cat = ScoreTable::ScoreCategory::THREES;
		break;
	case ScoreTable::ScoreCategory::THREES:
		cat = ScoreTable::ScoreCategory::FOURS;
		break;
	case ScoreTable::ScoreCategory::FOURS:
		cat = ScoreTable::ScoreCategory::FIVES;
		break;
	case ScoreTable::ScoreCategory::FIVES:
		cat = ScoreTable::ScoreCategory::SIXES;
		break;
	case ScoreTable::ScoreCategory::SIXES:
		cat = ScoreTable::ScoreCategory::THREE_OF_A_KIND;
		break;
	case ScoreTable::ScoreCategory::THREE_OF_A_KIND:
		cat = ScoreTable::ScoreCategory::FOUR_OF_A_KIND;
		break;
	case ScoreTable::ScoreCategory::FOUR_OF_A_KIND:
		cat = ScoreTable::ScoreCategory::FULLHOUSE;
		break;
	case ScoreTable::ScoreCategory::FULLHOUSE:
		cat = ScoreTable::ScoreCategory::SMALL_STRAIGHT;
		break;
	case ScoreTable::ScoreCategory::SMALL_STRAIGHT:
		cat = ScoreTable::ScoreCategory::BIG_STRAIGHT;
		break;
	case ScoreTable::ScoreCategory::BIG_STRAIGHT:
		cat = ScoreTable::ScoreCategory::YAHTZEE;
		break;
	case ScoreTable::ScoreCategory::YAHTZEE:
		cat = ScoreTable::ScoreCategory::CHANCE;
		break;
	case ScoreTable::ScoreCategory::CHANCE:
		cat = ScoreTable::ScoreCategory::TOTAL;
		break;
	}

	return cat;
}

std::ostream& operator<<(std::ostream& out, ScoreTable::ScoreCategory cat)
{
	switch (cat)
	{
	case ScoreTable::ScoreCategory::TOTAL:
		out << "Total";
		break;
	case ScoreTable::ScoreCategory::ONES:
		out << "Ones";
		break;
	case ScoreTable::ScoreCategory::TWOS:
		out << "Twos";
		break;
	case ScoreTable::ScoreCategory::THREES:
		out << "Threes";
		break;
	case ScoreTable::ScoreCategory::FOURS:
		out << "Fours";
		break;
	case ScoreTable::ScoreCategory::FIVES:
		out << "Fives";
		break;
	case ScoreTable::ScoreCategory::SIXES:
		out << "Sixes";
		break;
	case ScoreTable::ScoreCategory::THREE_OF_A_KIND:
		out << "Three of a kind";
		break;
	case ScoreTable::ScoreCategory::FOUR_OF_A_KIND:
		out << "Four of a kind";
		break;
	case ScoreTable::ScoreCategory::FULLHOUSE:
		out << "Fullhouse";
		break;
	case ScoreTable::ScoreCategory::SMALL_STRAIGHT:
		out << "Small straight";
		break;
	case ScoreTable::ScoreCategory::BIG_STRAIGHT:
		out << "Big straight";
		break;
	case ScoreTable::ScoreCategory::YAHTZEE:
		out << "Yahtzee!";
		break;
	case ScoreTable::ScoreCategory::CHANCE:
		out << "Chance";
		break;
	default:
		out << "No Category";
		break;
	}
	return out;

}

std::string ScoreTable::EnumToString(ScoreTable::ScoreCategory cat)
{
	switch (cat) {
	case ScoreTable::ScoreCategory::TOTAL:
		return "TOTAL";
	case ScoreTable::ScoreCategory::ONES:
		return "ONES";
	case ScoreTable::ScoreCategory::TWOS:
		return"TWOS";
	case ScoreTable::ScoreCategory::THREES:
		return "THREES";
	case ScoreTable::ScoreCategory::FOURS:
		return "FOURS";
	case ScoreTable::ScoreCategory::FIVES:
		return "FIVES";
	case ScoreTable::ScoreCategory::SIXES:
		return "SIXES";
	case ScoreTable::ScoreCategory::THREE_OF_A_KIND:
		return "THREE OF A KIND";
	case ScoreTable::ScoreCategory::FOUR_OF_A_KIND:
		return "FOUR OF A KIND";
	case ScoreTable::ScoreCategory::FULLHOUSE:
		return "FULLHOUSE";
	case ScoreTable::ScoreCategory::SMALL_STRAIGHT:
		return "SMALL STRAIGHT";
	case ScoreTable::ScoreCategory::BIG_STRAIGHT:
		return "BIG STRAIGHT";
	case ScoreTable::ScoreCategory::YAHTZEE:
		return "YAHTZEE";
	case ScoreTable::ScoreCategory::CHANCE:
		return "CHANCE";
	default:
		return "NOCATEGORY";
	}
}
