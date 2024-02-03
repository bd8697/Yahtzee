#pragma once
#include <vector>
#include<string>
#include "Player.h"

#include"AssetManager.h"
#include"InputManager.h"
#include"StateMachine.h"
#include<SFML/Graphics.hpp>
#include "../Winners/Winners/WinnersHierarchy.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
	WinnersHierarchy winners;

};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, const std::string& title);
	~Game();

	void Run();
	void StartGame();
	void nextPlayer();
    std::shared_ptr<Player> getCurrentPlayer();
	std::shared_ptr<Player> winner;

	std::vector<std::shared_ptr<Player>> players;
	sf::Clock _clock;
private:
	void TitleMenu(); // Allows you to see the rules of Yahtzee or start the game. (for now)
	void SetUpGame(); // Setupgame is called outside the game loop and it calls UpdateGame which will run unit CheckForGameOver is true.
	void UpdateGame(); // game engine
	// Maybe later we will split UpdateGame() into UpdateGameState() and UpdateGameOutput(), if needed
	void RefreshConsole();

public:
	bool CheckForGameOver();
	

private:
	void SetOrderOfPlayers();

	
	int i_currentPlayer;
	const float dt = 1.0f / 60.0f;

	GameDataRef _data = std::make_shared<GameData>();
};