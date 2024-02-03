#include "Game.h"
#include"MainMenu.h"
#include <iostream>

Game::Game(int width, int height, const std::string& title): i_currentPlayer(0)
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->machine.AddState(new MainMenu(this->_data, *this));
	this->Run();
}

Game::~Game()
{

}

void Game::StartGame()
{
	Game::TitleMenu();

	while (Game::CheckForGameOver() == false)
	{
		Game::RefreshConsole();
		Game::UpdateGame();
	}
}

void Game::TitleMenu()
{
	int option = 0;
	// temp
	std::cout << "YAHTZEE!" << std::endl; // center this
	std::cout << "1. View Rules" << std::endl;
	std::cout << "2. Play" << std::endl << std::endl;
	std::cout << "Choose an option:";

	std::cin >> option;
	do {
		if (option == 1)
		{
			// add rules
			break;
		}
		else if (option == 2)
		{
			Game::SetUpGame();
			break;
		}
		else 
		{
			std::cout << "Invalid option, please try again:";
			std::cin >> option;
		}
	} while (true);
}

void Game::SetUpGame()
{
	std::string auxName;
	int noOfPlayers = 0;

	while (noOfPlayers == 0)
	{
		try
		{
			std::cout << "Please enter the number of players: ";
			std::cin >> noOfPlayers;
			if (std::cin.fail())throw std::runtime_error("Error. Input is not a number. Try again. :)");

		}
		catch (const std::runtime_error & e)
		{
			std::cout << e.what() << "\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}
	while (noOfPlayers < 0 || noOfPlayers > 10)
	{
		std::cout << "Invalid number. Please try again: \n";
		bool ok = true;
		while (ok == true)
		{
			try
			{
				std::cout << "Please enter the number of players: ";
				std::cin >> noOfPlayers;
				if (std::cin.fail())throw std::runtime_error("Error. Input is not a number. Try again. :)");
				else ok = false;
			}
			catch (const std::runtime_error & e)
			{
				std::cout << e.what() << "\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}
	}
	for (int i = 0; i < noOfPlayers; i++)
	{
		bool k = true;
		while (k == true)
		{
			try
			{
				std::cout << "Please enter the name of player #" << (i + 1) << ": ";
				std::cin >> auxName;
				std::string::const_iterator it = auxName.begin();
				bool ok = false;
				while (it != auxName.end())
				{
					if (!isalpha(*it)) ok = true;
					it++;
				}
				if (ok == true)throw std::runtime_error("Error. Input is not a string. Try again. :)");
				else k = false;

			}
			catch (const std::runtime_error & e)
			{
				std::cout << e.what() << "\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}

		players.push_back(std::make_shared<Player>(auxName));
	}

	SetOrderOfPlayers();
}

void Game::nextPlayer()
{
    i_currentPlayer = (i_currentPlayer + 1) % players.size();
}

std::shared_ptr<Player> Game::getCurrentPlayer()
{
	return players[i_currentPlayer];
}

void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	while (this->_data->window.isOpen())  // 60 f/s 
	{
		this->_data->machine.ProcessStateChanges();
		newTime = _clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
}

void Game::SetOrderOfPlayers()
{
	int maxScore = 0;
	std::cout << "\n";
	std::cout << "First round of rolls is to decide who has the first turn.\n";
	for (int index = 0; index < players.size(); index++)
	{
		std::cout << players[index]->GetName() << "'s hand:\n";
		players[index]->Roll();
		std::cout << "score: " << players[index]->SumOfTotalDie() << "\n";
		if (players[index]->SumOfTotalDie() > maxScore)
		{
			maxScore = players[index]->SumOfTotalDie();
			i_currentPlayer = index;
		}
	}
}

void Game::UpdateGame()
{
	std::shared_ptr<Player> thisPlayer = players.at(i_currentPlayer);

	std::cout << "\n**" << thisPlayer->GetName() << "'s turn**\n\n";
	do
	{
		thisPlayer->Roll();
		thisPlayer->QueryCandidates();
		thisPlayer->DisplayScoreOptions();
	} while (!thisPlayer->TurnIsOver());

	thisPlayer->ScoreDice();
	thisPlayer->PrintScore();
	nextPlayer();
}

void Game::RefreshConsole()
{
}

bool Game::CheckForGameOver()
{
	for (const auto& player : players)
	{
		if (!player->SheetComplete())
		{
			return false;
		}
	}

	winner = players.at(0);

	for (const auto& player : players)
	{
		if (player->TotalScore() > winner->TotalScore())
		{
			winner = player;
		}
	}
	_data->winners.PopulateWinnersList(winner->GetName(),winner->TotalScore());
//	std::cout << "Winner " << winner->GetName() << " scored: " << winner->TotalScore() << std::endl;

	return true;
}
