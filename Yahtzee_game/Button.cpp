#include "Button.h"
#include<iostream>


Button::Button(std::string buttonText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor)
{
	button.setSize(buttonSize);
	button.setFillColor(bgColor);
	symbol.scale(0.3, 0.3);

	buttonWidth = buttonSize.x;
	buttonHeight = buttonSize.y;

	text.setString(buttonText);
	text.setCharacterSize(charSize);
	text.setFillColor(textColor);
}

void Button::SetFont(sf::Font& fonts)
{
	text.setFont(fonts);
}

void Button::SetBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::SetTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::SetTextureOn(const std::string& path)
{
	if (!textureOn.loadFromFile(path))
	{
		std::cout << "Error on loading image!";
	}
	textureOn.setSmooth(true);
}

void Button::SetTextureOff(const std::string& path)
{
	if (!textureOff.loadFromFile(path))
	{
		std::cout << "Error on loading image!";
	}
	textureOff.setSmooth(true);
}

void Button::ChangeTexture(bool pressed)
{
	if (pressed == true)
	{
		symbol.setTexture(textureOff);
	}
	else
	{
		symbol.setTexture(textureOn);
	}
}

void Button::SetPosition(sf::Vector2f point)
{
	symbol.setPosition(point);
	button.setPosition(point);
	// Center text on button:
	float xPos = (point.x + buttonWidth / 2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + buttonHeight / 2.2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(symbol);
	window.draw(text);
}

bool Button::IsMouseOver(sf::RenderWindow& window)
{
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int buttonPosX = symbol.getPosition().x;
	int buttonPosY = symbol.getPosition().y;

	int buttonPosWidth = buttonPosX + buttonWidth;
	int buttonPosHeight = buttonPosY + buttonHeight;

	if (mouseX < buttonPosWidth && mouseX > buttonPosX && mouseY < buttonPosHeight && mouseY > buttonPosY) {
		return true;
	}
	return false;
}
