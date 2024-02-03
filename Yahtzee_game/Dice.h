#pragma once
#include "Die.h"
#include <vector>
#include <iostream>
#include <exception>
#include <array>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>
#include <memory>

class Dice
{
public:
	explicit Dice(short int argTotal = 5, int rolls = 3);
	~Dice();

	void DiceRoll();
	void Print() const;
	void DrawHand(sf::RenderWindow& window, const float& scale, const float& size, const float& pozX, const float& pozY, const int& alpha);
	void DecreaseRolls();
	int GetRollsLeft();
	void SetRollsLeft(const int& rolls);
	void ReleaseAllDice();
	void ToggleDice(unsigned int argIndex);
    std::array<std::shared_ptr<Die>, 5>& GetDiceArray();


private:
	short int total;
	int rollsLeft;
	int clickedOn = 0;
	int clickedOnCounter = 0;
	std::array<std::shared_ptr<Die>, 5> diceArray;
	std::array<mySprite, 5> diceContainer;
	sf::SoundBuffer soundBuffer;
	sf::SoundBuffer soundBuffer2;
	sf::Sound tap;
	sf::Sound au;
};


