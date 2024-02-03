#include "mySprite.h"
#include <iostream>

mySprite::mySprite(const std::string& path)
{

	if (!theSprite_txt.loadFromFile(path))
	{
		std::cout << "Error loading image!";
	}
	theSprite_txt.setSmooth(true);
	theSprite.setTexture(theSprite_txt);
}

mySprite::mySprite()
{
	// empty
}

void mySprite::SetTexture(const std::string& path)
{

	if (!theSprite_txt.loadFromFile(path))
	{
		std::cout << "Error loading image!";
	}
	theSprite_txt.setSmooth(true);
	theSprite.setTexture(theSprite_txt);

	width = theSprite.getGlobalBounds().width;
	height = theSprite.getGlobalBounds().height;
	
}

bool mySprite::IsMouseOver(sf::RenderWindow& window)
{
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int buttonPosX = theSprite.getPosition().x;
	int buttonPosY = theSprite.getPosition().y;

	int buttonPosWidth = theSprite.getPosition().x + theSprite.getScale().x;
	int buttonPosHeight = theSprite.getPosition().y + theSprite.getScale().y;

	if (mouseX < buttonPosWidth && mouseX > buttonPosX&& mouseY < buttonPosHeight && mouseY > buttonPosY) {
		return true;
	}
		return false;
}
