#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <vector>

class Laser
{
public:
	Laser(GameDataRef data);

	void SpawnLaser();
	void MoveLaser(float dt);
	void DrawLaser();
	void DeleteLaser();

	const std::vector<sf::Sprite> &GetSprites() const;

	/////////////////////////////////////////////////////// spaghetti
	void Update(float dt);
	void MoveU();
	void MoveD();
	void MoveR();
	void MoveL();

private:
	GameDataRef _data;

	std::vector<sf::Sprite> LaserSprites;
	int movespeedL = 500;

	//////////////////////////////////////////////////////////////////  spaghetti
	sf::Sprite ShipSprite;
	sf::Clock moveClock; 
	int moveSpeed = 250;
	float moveDuration = 0.5;
	int ShipState;
	enum MoveState
	{
		eLeft,
		eRight,
		eUp,
		eDown,
		eStop
	};
};

