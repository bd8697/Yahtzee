#pragma once
#include <SFML\Graphics.hpp>
#include <string>
//a Sprite is lightweight, not memory intensive, while a texture eats a lot of memory
class mySprite {

public:
	sf::Sprite theSprite; // I want it to be public
	sf::Texture theSprite_txt;
	mySprite(const std::string& path);
	mySprite();
	int width;
	int height;
	// implement these, if needed
	void SetTexture(const std::string& path);
	bool IsMouseOver(sf::RenderWindow& window);

	//	void SetPosition(sf::Sprite& sprite, const int& x, const int& y);
	//	void SetDimiensions(sf::Sprite& sprite, const int& x, const int& y);
};