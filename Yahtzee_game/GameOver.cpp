#include "GameOver.h"
#include "MainMenu.h"



#include <sstream>
#include<iostream>
#include <string>
#include <fstream>
#include <streambuf>

GameOver::GameOver(GameDataRef& data, Game& game) : _data(data), _game(game)
{
}

void GameOver::Init()
{
	//Title
	_data->assets.LoadTexture("Game Over Title", "../assetz/game-over.png");
	gameOverTitle.setTexture(_data->assets.GetTexture("Game Over Title"));
	gameOverTitle.setPosition(_data->window.getSize().x /1.8 - gameOverTitle.getGlobalBounds().width/2,
		 (_data->window.getSize().y / 2) - (gameOverTitle.getGlobalBounds().height / 2));
	gameOverTitle.scale(0.8f, 0.8f);

	//Play Again button
	hierarchyButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	hierarchyButton->SetPosition({ (float)(this->_data->window.getSize().x / 2.7), (float)(this->_data->window.getSize().y / 1.5) });

	//Main Menu button
	mainMenuButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	mainMenuButton->SetPosition({ (float)(this->_data->window.getSize().x / 2.4), (float)(this->_data->window.getSize().y / 1.3) });

	//Exit button
	exitButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	exitButton->SetPosition({ (float)(this->_data->window.getSize().x / 2.4), (float)(this->_data->window.getSize().y / 1.15) });
}


void GameOver::HandleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->_data->window.close();
			break;
		}
		case sf::Event::MouseMoved:
		{
			if (hierarchyButton->IsMouseOver(this->_data->window)) {
				hierarchyButton->SetBackColor(sf::Color::White);
			}
			else {
				hierarchyButton->SetBackColor(sf::Color::Black);
			}
			if (mainMenuButton->IsMouseOver(this->_data->window)) {
				mainMenuButton->SetBackColor(sf::Color::White);
			}
			else {
				mainMenuButton->SetBackColor(sf::Color::Black);
			}
			if (exitButton->IsMouseOver(this->_data->window)) {
				exitButton->SetBackColor(sf::Color::White);
			}
			else {
				exitButton->SetBackColor(sf::Color::Black);
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (hierarchyButton->IsMouseOver(this->_data->window)) {

				
				SeeHierarchy();
			}

			if (mainMenuButton->IsMouseOver(this->_data->window)) {
				_data->machine.AddState(new MainMenu(_data, _game), true);
			}

			if (exitButton->IsMouseOver(this->_data->window)) {
				this->_data->window.close();
			}
			break;
		}
		}
	}
}

void GameOver::Update(float dt)
{
}

void GameOver::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(backgroundgr, 4, sf::Quads);
	_data->window.draw(gameOverTitle);
    hierarchyButton->Draw(_data->window);
	mainMenuButton->Draw(_data->window);
	exitButton->Draw(_data->window);
	_data->window.display();
}

void GameOver::SeeHierarchy()
{
	sf::RenderWindow hierarchyWindow(sf::VideoMode(600, 900), "Winners Hierarchy");
	sf::Font hierarchyFont;
	hierarchyFont.loadFromFile("../assetz/arial.ttf");
	sf::Text hierarchyTextContent;
	hierarchyTextContent.setFont(hierarchyFont);
	hierarchyTextContent.setFillColor(sf::Color::Black);
	hierarchyTextContent.setCharacterSize(11);
	hierarchyTextContent.setStyle(sf::Text::Regular);
	hierarchyTextContent.setPosition(50, 15);

	std::ifstream hierarchyFileStream("../Winners/Winners/Hierarchy.txt");
	std::string instructionsString;

	hierarchyFileStream.seekg(0, std::ios::end);
	instructionsString.reserve(hierarchyFileStream.tellg());
	hierarchyFileStream.seekg(0, std::ios::beg);

	instructionsString.assign((std::istreambuf_iterator<char>(hierarchyFileStream)),
		std::istreambuf_iterator<char>());

	sf::String Text(instructionsString);
	hierarchyTextContent.setString(instructionsString);

	while (hierarchyWindow.isOpen())
	{
		sf::Event event;
		while (hierarchyWindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				hierarchyWindow.close();
		}

		hierarchyWindow.clear(sf::Color::White);
		hierarchyWindow.draw(hierarchyTextContent);
		hierarchyWindow.display();
	}

}
