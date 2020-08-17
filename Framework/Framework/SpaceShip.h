#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <vector>

class SpaceShip
{
public:
	SpaceShip(GameDataRef data); // constructor and deconstructor
	~SpaceShip() {}

	void Draw();
	void Update(float dt);
	void MoveU();
	void MoveD();
	void MoveR();
	void MoveL();

	const sf::Sprite &Sprite() const;  //method returns ref to sprite which we pass to collsion method to check for collision 
	
private:
	GameDataRef _data;
	sf::Sprite ShipSprite;

	// movement varables to controll the state based movement
	int MoveSpeed = 250;
	float MoveDuration = 0.5;
	int ShipState;
	sf::Clock moveClock; 
	enum MoveState  // mini state machine dictating which direction we move in
	{
		eLeft,
		eRight,
		eUp,
		eDown,
		eStop
	};	
};


