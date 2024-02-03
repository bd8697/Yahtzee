#include "MainMenu.h"
#include "PlayState.h"
#include "GameOver.h"

#include <sstream>
#include<iostream>
#include <string>
#include <fstream>
#include <streambuf>


MainMenu::MainMenu(GameDataRef& data, Game& game) : _data(data) , _game(game)
{
}

void MainMenu::Init() 
{
	_data->assets.LoadFont("Buttons font1", "../assetz/Fonts/Angelina Alt Demo.ttf");
	_data->assets.LoadFont("Buttons font2", "../assetz/Fonts/Righteous-Regular.ttf");
	_data->assets.LoadTexture("Dice", "../assetz/yahtzee.png");
	_data->assets.LoadTexture("Yahtzee logo", "../assetz/yahtzeeLogo.png");

	//	int fontSize = _data->window.getSize().x / 50;
	text.setFont(_data->assets.GetFont("Buttons font2"));
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	//Play button
	playButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	playButton->SetPosition({ (float)(this->_data->window.getSize().x / 2.35), (float)(this->_data->window.getSize().y / 3.5) });

	//Instructions button
	instructionsButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	instructionsButton->SetPosition({ (float)(this->_data->window.getSize().x / 4), (float)(this->_data->window.getSize().y / 2.5) });

	//Add player button
	addPlayerButton->SetFont(this->_data->assets.GetFont("Buttons font2"));
	addPlayerButton->SetPosition({ (float)(this->_data->window.getSize().x / 1.7), (float)(this->_data->window.getSize().y / 2.5) });


	//Dice
	dice.setTexture(_data->assets.GetTexture("Dice"));
	dice.scale(0.2f, 0.2f);
	dice.setPosition(_data->window.getSize().x / 2- dice.getGlobalBounds().width/2, _data->window.getSize().y / 2+ dice.getGlobalBounds().height/1.4);

	//Logo
	logo.setTexture(_data->assets.GetTexture("Yahtzee logo"));
	logo.scale(0.4f, 0.4f);
	logo.setPosition(_data->window.getSize().x / 2 - dice.getGlobalBounds().width /1.2, _data->window.getSize().y / 2 - dice.getGlobalBounds().height*1.6);

}

void MainMenu::HandleInput()
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
			if (_game.players.size() > 0 && playButton->IsMouseOver(this->_data->window)) {
				playButton->SetBackColor(sf::Color::White);
			}
			else {
				playButton->SetBackColor(sf::Color(252, 247, 94));
			}
			if (instructionsButton->IsMouseOver(this->_data->window)) {
				instructionsButton->SetBackColor(sf::Color::White);
			}
			else {
				instructionsButton->SetBackColor(sf::Color(252, 247, 94));
			}
			if (addPlayerButton->IsMouseOver(this->_data->window)) {
				addPlayerButton->SetBackColor(sf::Color::White);
			}
			else {
				addPlayerButton->SetBackColor(sf::Color(252, 247, 94));
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (_game.players.size() > 0 && playButton->IsMouseOver(this->_data->window)) {
				_data->machine.AddState(new PlayState(_data, _game), true);
				//_data->machine.AddState(new GameOver(_data, _game), true);
			}

			if (instructionsButton->IsMouseOver(this->_data->window)) {
				SeeInstructions();
			}

			if (addPlayerButton->IsMouseOver(this->_data->window)) {
				if (listenForName == false)
				{
					listenForName = true;
				}
			}
			break;
		}
		case sf::Event::TextEntered:
		{
			if (listenForName)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					AddPlayer();
					listenForName = false;
					auxName = "";
				}
				else
				{
					if (event.text.unicode == '\b' && auxName.size() > 0) {
						auxName.erase(auxName.size() - 1, 1);
					}
					else if (event.text.unicode < 128) {
						auxName += event.text.unicode;
					}
					text.setString(auxName);
				}
			}
		}
		}
	}
	
}

void MainMenu::Update(float dt)
{
}

void MainMenu::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(backgroundgr, 4, sf::Quads);
	_data->window.draw(dice);
	_data->window.draw(logo);
	if(_game.players.size()>0)
	playButton->Draw(_data->window);
	instructionsButton->Draw(_data->window);
	addPlayerButton->Draw(_data->window);
	DrawPlayers();
	_data->window.display();
}

void MainMenu::AddPlayer()
{
    _game.players.push_back(std::make_shared<Player>(auxName));
}

void MainMenu::DrawPlayers()
{
	if (listenForName)
	{
		text.setString("Your name: " + auxName);
		text.setPosition(this->_data->window.getSize().x / 4, this->_data->window.getSize().y / 2.2);
		_data->window.draw(text);
	}
	for (int i = 0; i < _game.players.size(); i++)
	{
		text.setString("Player " + std::to_string(i+1) + " :" + _game.players[i]->GetName());
		text.setPosition(this->_data->window.getSize().x / 4, this->_data->window.getSize().y / 2 + i * 40);
		_data->window.draw(text);
	}
}

void MainMenu::SeeInstructions()
{
	sf::RenderWindow instructionsWindow(sf::VideoMode(600, 900), "Instructions");
	sf::Font instructionsFont;
	instructionsFont.loadFromFile("../assetz/arial.ttf");
	sf::Text instructionsTextContent;
	instructionsTextContent.setFont(instructionsFont);
	instructionsTextContent.setFillColor(sf::Color::Black);
	instructionsTextContent.setCharacterSize(11);
	instructionsTextContent.setStyle(sf::Text::Regular);
	instructionsTextContent.setPosition(50, 15);

	std::ifstream instructionsFileStream("../assetz/Instructions.txt");
	std::string instructionsString;

	instructionsFileStream.seekg(0, std::ios::end);
	instructionsString.reserve(instructionsFileStream.tellg());
	instructionsFileStream.seekg(0, std::ios::beg);

	instructionsString.assign((std::istreambuf_iterator<char>(instructionsFileStream)),
		std::istreambuf_iterator<char>());

	sf::String Text(instructionsString);
	instructionsTextContent.setString(instructionsString);

	while (instructionsWindow.isOpen())
	{
		sf::Event event;
		while (instructionsWindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				instructionsWindow.close();
		}

		instructionsWindow.clear(sf::Color::White);
		instructionsWindow.draw(instructionsTextContent);
		instructionsWindow.display();
	}


}
