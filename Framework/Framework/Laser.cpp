#include "Laser.h"
#include <iostream>

Laser::Laser(GameDataRef data) : _data(data)
{
	ShipSprite.setPosition((_data->window.getSize().x / 2) - (ShipSprite.getGlobalBounds().width / 2),
		(_data->window.getSize().y / 2) + (_data->window.getSize().y / 4) - (ShipSprite.getGlobalBounds().height / 2));
}

void Laser::SpawnLaser()
{
	sf::Sprite sprite(this->_data->assets.GetTexture("Laser")); //creating a sprite, initialise it with the asset 

	sprite.setPosition(ShipSprite.getPosition().x - 3, ShipSprite.getPosition().y - 40);

	LaserSprites.push_back(sprite); // pusing on the sprite to the vector
}

void Laser::MoveLaser(float dt)
{
	for (int i = 0; i < LaserSprites.size(); i++)
	{
		if (LaserSprites.at(i).getPosition().y < 0) 
		{
			LaserSprites.erase(LaserSprites.begin() + i); 
		}
		else
		{
			float movement = movespeedL * dt; 

			LaserSprites.at(i).move(0, -movement);
		}
	}
}

void Laser::DrawLaser()
{
	for (unsigned short int i = 0; i < LaserSprites.size(); i++) // loop over the pipe vector
	{
		this->_data->window.draw(LaserSprites.at(i));
	}
}

const std::vector<sf::Sprite> &Laser::GetSprites() const //now we can have acces to our pipes in our game state
{
	return LaserSprites;
}

void Laser::DeleteLaser()
{
	LaserSprites.erase(LaserSprites.begin());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////  spaghetti code down below beware.

void Laser::Update(float dt) //state based movement
{
	if (eStop == ShipState)
	{
		ShipSprite.move(0, 0);
	}
	else if (eUp == ShipState)
	{
		ShipSprite.move(0, -moveSpeed * dt);
	}
	else if (eDown == ShipState)
	{
		ShipSprite.move(0, +moveSpeed * dt);
	}
	else if (eRight == ShipState)
	{
		ShipSprite.move(+moveSpeed * dt, 0);
	}
	else if (eLeft == ShipState)
	{
		ShipSprite.move(-moveSpeed * dt, 0);
	}

	if (moveClock.getElapsedTime().asSeconds() > moveDuration)
	{
		moveClock.restart();
		ShipState = eStop;
	}
}

void Laser::MoveU() // all the function that are called using the input manager and setting the state for the movement in the update function above
{
	moveClock.restart();
	ShipState = eUp;
}
void Laser::MoveD()
{
	moveClock.restart();
	ShipState = eDown;
}
void Laser::MoveR()
{
	moveClock.restart();
	ShipState = eRight;
}
void Laser::MoveL()
{
	moveClock.restart();
	ShipState = eLeft;
}

