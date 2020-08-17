#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <vector>

class Asteroid
{
public:
	Asteroid(GameDataRef data);

	void SpawnAsteroid();
	void MoveAsteroid(float dt);
	void DeleteAsteroid();
	void DrawAsteroid();
	void RandomiseAsteroid();

	const std::vector<sf::Sprite> &GetSprites() const;
	
private:
	GameDataRef _data;

	//variables for spawning and moving
	std::vector<sf::Sprite> asteroidSprites;
	int moveSpeed = 200;
	int offset; 
};
