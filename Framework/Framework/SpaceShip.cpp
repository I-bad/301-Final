#include "SpaceShip.h"
#include <iostream>

SpaceShip::SpaceShip(GameDataRef data) : _data(data) // game data ref being assigned to the data
{
	ShipSprite.setTexture(this->_data->assets.GetTexture("Spaceship")); //setting the texture laoing it in game state

	ShipSprite.setPosition((_data->window.getSize().x / 2) - (ShipSprite.getGlobalBounds().width / 2), 
		(_data->window.getSize().y / 2) + (_data->window.getSize().y / 4) - (ShipSprite.getGlobalBounds().height / 2));
}

void SpaceShip::Draw()
{
	_data->window.draw(ShipSprite); //draw the sprite
}

void SpaceShip::Update(float dt) //state based movement
{
	if (eStop == ShipState)
	{
		ShipSprite.move(0, 0);
	}
	else if (eUp == ShipState)
	{
		ShipSprite.move(0, -MoveSpeed * dt);
	}
	else if (eDown == ShipState)
	{
		ShipSprite.move(0, +MoveSpeed * dt);
	}
	else if (eRight == ShipState)
	{
		ShipSprite.move(+MoveSpeed * dt, 0);
	}
	else if (eLeft == ShipState)
	{
		ShipSprite.move(-MoveSpeed * dt, 0);
	}
	if (moveClock.getElapsedTime().asSeconds() > MoveDuration)
	{
		moveClock.restart();
		ShipState = eStop;
	}
}

void SpaceShip::MoveU() // all the function that are called using the input manager and setting the state for the movement in the update function above
{
	moveClock.restart();
	ShipState = eUp;
}
void SpaceShip::MoveD()
{
	moveClock.restart();
	ShipState = eDown;
}
void SpaceShip::MoveR()
{
	moveClock.restart();
	ShipState = eRight;
}
void SpaceShip::MoveL()
{
	moveClock.restart();
	ShipState = eLeft;
}
	
const sf::Sprite &SpaceShip::Sprite() const //retunrns the sprite of the object so we can use it in the collision system
{
	return ShipSprite;
}
