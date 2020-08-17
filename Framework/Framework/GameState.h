#pragma once
#include <SFML/Graphics.hpp>
#include "State.h" // this will inherit from the state calss since it is a state
#include "Engine.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "Collision.h"
#include "Laser.h"
#include "MainMenuState.h"
#include "FPS.h"
class GameState : public State
{
public:
	GameState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;  // local refernce for the game data
	sf::Sprite  background;
	sf::Clock clock; // clock used for spawning rock bois

	//pointer to the object classes thw we assign in the initialisation of the game state
	FPS *fps;
	Asteroid *asteroid; 
	SpaceShip *spaceShip; 
	Laser *laser;
	Collision collision; //this is not a pointer, we dont need to reconstruct, the default constructer is fine

	float deathPause = 1.25;
	float spawnRate = 1.25;

	int gameState; //game state variable for state machine
	enum GameStates // mini state machine for game state class
	{
		eReady,
		ePlaying,
		eGameOver
	};
};
