#pragma once
#include<SFML/Graphics.hpp>
#include"GameState.h"
#include"Game.h"
#include "Button.h"

class GameOver : public GameState
{
public:
	GameOver(GameDataRef& data, Game& game);


	void Init()override;
	void HandleInput()override;
	void Update(float dt)override;
	void Draw(float dt)override;
	void SeeHierarchy();

private:

	Game& _game;
	GameDataRef _data;
	sf::Vertex backgroundgr[4] =
	{
			sf::Vertex(sf::Vector2f(0, 0), sf::Color(55, 0, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, 0), sf::Color(55, 0, 0)),
			sf::Vertex(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y), sf::Color(255,0,0)),
			sf::Vertex(sf::Vector2f(0,_data->window.getSize().y),sf::Color(255,0,0))
	};
	Button* hierarchyButton = new Button("Winners Hierarchy", { 200, 40 }, 22, sf::Color::Black, sf::Color(255, 0, 0));
	Button* mainMenuButton = new Button("Main Menu", { 120, 40 }, 22, sf::Color::Black, sf::Color(255, 0, 0));
	Button* exitButton = new Button("Exit", { 120, 40 }, 22, sf::Color::Black, sf::Color(255, 0, 0));

	sf::Font font;
	sf::Text text;
	sf::Sprite gameOverTitle;
};

