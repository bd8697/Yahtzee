#pragma once
#include <SFML/Graphics.hpp>
#include "MySprite.h"
#include <string>

class Button
{
	public:
		Button(std::string buttonText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

		void SetFont(sf::Font& fonts);

		void SetBackColor(sf::Color color);

		void SetTextColor(sf::Color color);

		void SetTexture(const std::string& path);

		void SetTextureOn(const std::string& path);

		void SetTextureOff(const std::string& path);

		void ChangeTexture( bool pressed);

		void SetPosition(sf::Vector2f point);

		void Draw(sf::RenderWindow& window);

		bool IsMouseOver(sf::RenderWindow& window);

	private:
	    sf::Sprite symbol;
		sf::Texture textureOn;
		sf::Texture textureOff;
		sf::Text text;
		sf::RectangleShape button;
		sf::Font font;

		int buttonWidth;
		int buttonHeight;
};

