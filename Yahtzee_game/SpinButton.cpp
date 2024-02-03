#include "SpinButton.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <iostream>

SpinButton::SpinButton()
{
	spinButton.SetTexture("../assetz/LoadingCircleGreen.png");
	spinButton.theSprite.setTextureRect(sf::IntRect(0, 0, spinButton.height, spinButton.height));

	int fontSize = 50;
	try {
		font.loadFromFile("../assetz/Fonts/Righteous-Regular.ttf");
	}
	catch (int e) {
		std::cout << "Font could not be loaded.";
	}

	rollsLeft.setFont(font);
	rollsLeft.setString(" 3");
	rollsLeft.setCharacterSize(fontSize);
	rollsLeft.setFillColor(sf::Color(252, 247, 94));
	rollsLeft.setStyle(sf::Text::Bold);

	soundBuffer.loadFromFile("../assetz/dice-roll.wav");
	roll.setBuffer(soundBuffer);

	lastTick = 0;
}

void SpinButton::SetPosition(sf::RenderWindow& window) // make it generic
{
	spinButton.theSprite.setPosition(window.getSize().x / 2 - spinButton.height / 2, window.getSize().y / 5);
	rollsLeft.setString("3");
	rollsLeft.setPosition((window.getSize().x - rollsLeft.getLocalBounds().width - 7) / 2, window.getSize().y / 5 - spinButton.height / 1.25);
}

void SpinButton::UpdateRolls(const int& rolls, sf::RenderWindow& window)
{
	if (rolls == 0)
	{
		rollsLeft.setFillColor(sf::Color(255, 36, 0));
	}
	else
	{
		rollsLeft.setFillColor(sf::Color(252, 247, 94));
	}
	rollsLeft.setString(std::to_string(rolls));
	rollsLeft.setPosition((window.getSize().x - rollsLeft.getLocalBounds().width - 7) / 2, window.getSize().y / 5 - spinButton.height / 1.25);
}

bool SpinButton::Spin(sf::RenderWindow& window, sf::Clock& clock, const int& rolls, const bool canSpin)
{
	mousePos = sf::Mouse::getPosition(window);

	if (loops > 0) {
		double tick = clock.getElapsedTime().asSeconds();
		if (tick - lastTick > 0.03) // todo: figure out the value for 60 fps cap
		{
			lastTick = tick;
			loops--;
			spinButton.theSprite.setTextureRect(sf::IntRect(spinButton.height * (loops % 8), 0, spinButton.height, spinButton.height));
		}
	}
	else if (canSpin && rolls > 0
		&& mousePos.x > (window.getSize().x / 2 - spinButton.height / 2)
		&& mousePos.x < (window.getSize().x / 2 + spinButton.height / 2)
		&& mousePos.y > (window.getSize().y / 5)
		&& mousePos.y < (window.getSize().y / 5 + spinButton.height)) // todo: store window size in varriable (saves time)
	{
		if (!inButton) { // so we dont have to change the texture every frame
			spinButton.SetTexture("../assetz/LoadingCircleRed.png");
			inButton = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && loops == 0)
		{
			loops = maxLoops * 8;
			roll.play();
			window.draw(rollsLeft);
			window.draw(spinButton.theSprite);
			return true;
		}
	}
	else // ( if mouse is out or out of rolls)
	{
		spinButton.SetTexture("../assetz/LoadingCircleGreen.png");
		inButton = false;
	}
	window.draw(rollsLeft);
	window.draw(spinButton.theSprite);
	return false;
	// draw sprite form spritesheet texture, with position relative to count
}
