#pragma once

#include<SFML/Graphics.hpp>
#include"GameState.h"
#include"Game.h"
#include "Button.h"

class MainMenu : public GameState
{
public:
	MainMenu(GameDataRef& data, Game& game);
	

	void Init()override;
	void HandleInput()override;
	void Update(float dt)override;
	void Draw(float dt)override;

private:

	void AddPlayer();
	void DrawPlayers();
	void SeeInstructions();

	Game& _game;
	GameDataRef _data;
	sf::Vertex backgroundgr[4] =
	{
			sf::Vertex(sf::Vector2f(0, 0), sf::Color(55, 0, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, 0), sf::Color(55, 0, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y), sf::Color(255,0,0)),
			sf::Vertex(sf::Vector2f(0,_data->window.getSize().y),sf::Color(255,0,0))
	};
	Button* playButton = new Button("Play", { 120, 40 }, 18, sf::Color(252, 247, 94), sf::Color::Black);
	Button* instructionsButton = new Button("Instructions", { 120, 40 }, 18, sf::Color(252, 247, 94), sf::Color::Black);
	Button* addPlayerButton = new Button("Add Player", { 120, 40 }, 18, sf::Color(252, 247, 94), sf::Color::Black);

	std::string auxName;
	bool listenForName = false;
	sf::Font font;
	sf::Text text;
	sf::Sprite dice;
	sf::Sprite logo;

};
