#pragma once
#include <map>
#include <SFML/Graphics.hpp>

// The AssetManager class provides long-lived access to sf::Textures 
// we can use thise asset manager and load the image once and set it multiple time
class AssetManager
{
public:
	AssetManager() {}
	~AssetManager() {}

	void LoadTexture(std::string name, std::string fileName); // this finction loads the texture with the prameters of a name for it and the directory itself 
	sf::Texture &GetTexture(std::string name); //this method allows us to get the texture using name that we set above and have a refence to it

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);

private:
	std::map<std::string, sf::Texture> textures; // this is the map that is storing the texture - name of the texute and texture itself 
	std::map<std::string, sf::Font> fonts;
};
