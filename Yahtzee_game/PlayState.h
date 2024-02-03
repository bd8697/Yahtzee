#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include"GameState.h"
#include"Game.h"
#include "Button.h"
#include "ScoreTable.h"
#include "SpinButton.h"
#include "MainMenu.h"

class PlayState : public GameState
{
public:
	PlayState(GameDataRef data, Game& game);

	void Init()override;
	void HandleInput()override;
	void Update(float dt)override;
	void Draw(float dt)override;

private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Clock _roundClock;
	Game& _game;

	//Table
	Die scaleDie;
	float dieScale;
	float dieSize;
	float drawAtX;
	float drawAtY;
	sf::Vertex backgroundgr[4] =
	{
			sf::Vertex(sf::Vector2f(0, 0), sf::Color(9, 34, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, 0), sf::Color(9, 34, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y), sf::Color(38, 141, 0)),
			sf::Vertex(sf::Vector2f(0,_data->window.getSize().y),sf::Color(38, 141, 0))
	};
	sf::Font font;
	sf::Text text;
	sf::Text playerTurn;

	//Sound 
	Button* soundButton = new Button("", { 120, 40 }, 30, sf::Color::Transparent, sf::Color::Black);
	bool musicOn = true;
	sf::Music music;

	//Spin button
	SpinButton spinButton;
	int timer = 0;
	int alpha = 0;

	//clock
	sf::Text timeText;
	sf::Text alertText;
	sf::Time elapsedTime;
	sf::String minutesString;
	sf::String secondsString;
	sf::String timeDotsString = ':';

	uint8_t minutes;
	uint8_t seconds;
	uint8_t roundSeconds;
	float alertTextAlpha;
	bool altertTextReverse;

	//game over
	sf::Sprite container;
	sf::Sprite crown;
	sf::Text winnerName;
	sf::Text winnerScore;

	

};