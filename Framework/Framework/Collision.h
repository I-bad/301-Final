#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision() {}
	~Collision() {}

	bool SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2); //method which is a bool to check sprite collision between 2 sprites
};
