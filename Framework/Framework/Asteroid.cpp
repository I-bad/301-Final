#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(GameDataRef data) : _data(data)
{
	offset = 0;
}

void Asteroid::SpawnAsteroid()
{
	sf::Sprite sprite(this->_data->assets.GetTexture("Asteroid")); //creating a sprite, initialise it with the asteroid asset 

	sprite.setPosition(this->_data->window.getSize().x - 15 - offset, 
		this->_data->window.getSize().y - this->_data->window.getSize().y - sprite.getLocalBounds().height);
		
	asteroidSprites.push_back(sprite); // pusing on the sprite to the vector
}

void Asteroid::MoveAsteroid(float dt)
{
	for (int i = 0; i < asteroidSprites.size(); i++) // loop over the asteroid vector
	{
		if (asteroidSprites.at(i).getPosition().y > 850) // if the asteroid goes off the screen
		{
			asteroidSprites.erase(asteroidSprites.begin() + i); //erase asteroid at the 1st asteroid in the vector
		}
		else
		{
			float movement = moveSpeed * dt; // calculate the movement

			asteroidSprites.at(i).move(0, movement); // moving the asteroids donw y 
		}
	}
}

void Asteroid::DeleteAsteroid()
{
	asteroidSprites.erase(asteroidSprites.begin());
}

void Asteroid::DrawAsteroid() //method for drawing the asteroids
{
	for (unsigned short int i = 0; i < asteroidSprites.size(); i++) // loop over the asteroid vector
	{
		this->_data->window.draw(asteroidSprites.at(i));
	}
}

void Asteroid::RandomiseAsteroid()
{
	offset = rand() % (this->_data->window.getSize().x); // basic randomize, and pick betoween 0 the screen width
}

const std::vector<sf::Sprite> &Asteroid::GetSprites() const //now we can have acces to our asteroids in our game state
{
	return asteroidSprites;
}
