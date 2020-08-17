#include <SFML/Graphics.hpp>
#include "AssetManager.h"

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture text; //local texture instance

	if (text.loadFromFile(fileName)) // if we succesfully load the file we pass in 
	{	
		this->textures[name] = text; // add it to the map of textures in the name param
	}
}

sf::Texture &AssetManager::GetTexture(std::string name) 
{
	return this->textures.at(name); // return the texture reference
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		this->fonts[name] = font;
	}
}

sf::Font &AssetManager::GetFont(std::string name)
{
	return this->fonts.at(name);
}
