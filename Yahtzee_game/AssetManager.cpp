#include "AssetManager.h"

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName))
	{
		this->_textures[name] = tex;
	}
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	return this->_textures.at(name);
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName))
	{
		this->_fonts[name] = font;
	}
}

sf::Font& AssetManager::GetFont(const std::string& name)
{
	return this->_fonts.at(name);
}
