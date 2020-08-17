#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "GameState.h"

GameState::GameState(GameDataRef data) : _data(data)
{
}

void GameState::Init()
{
	//casting the values from our level.lua file to these variables using the level editor class
	lua_State* F = this->_data->levelEditor.setupLuaFile("level.lua");
	LuaRef w = this->_data->levelEditor.getLuaStackProperty(F, "directories", "Background");
	LuaRef s = this->_data->levelEditor.getLuaStackProperty(F, "directories", "SpaceShip");
	LuaRef l = this->_data->levelEditor.getLuaStackProperty(F, "directories", "Laser");
	LuaRef a = this->_data->levelEditor.getLuaStackProperty(F, "directories", "Asteroid");

	//using thew asset manager to load/set  textures/fonts that will be used on this state for the
	this->_data->assets.LoadFont("Font", "../Textures/HolySans.ttf");
	this->_data->assets.LoadTexture("Game Background", w);
	this->_data->assets.LoadTexture("Asteroid", a);
	this->_data->assets.LoadTexture("Spaceship", s);
	this->_data->assets.LoadTexture("Laser", l);
	background.setTexture(this->_data->assets.GetTexture("Game Background"));

	asteroid = new Asteroid(_data); // access object with the data ref so we can access everything from the windown and what else/construct the object
	spaceShip = new SpaceShip(_data);
	laser = new Laser(_data);
	fps = new FPS(_data);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event)) 
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		if (GameStates::eGameOver != gameState)
		{

			if (this->_data->input.ClickedU(sf::Keyboard::Up)) // acceses the different input function implemented into the input manager
			{
				gameState = GameStates::ePlaying;
				spaceShip->MoveU(); 
				laser->MoveU();
				this->_data->enetClient.SendMovementPacket(this->spaceShip->Sprite().getPosition().x, this->spaceShip->Sprite().getPosition().y);
			}
			if (this->_data->input.ClickedD(sf::Keyboard::Down))
			{
				gameState = GameStates::ePlaying;
				spaceShip->MoveD();
				laser->MoveD();
				this->_data->enetClient.SendMovementPacket(this->spaceShip->Sprite().getPosition().x, this->spaceShip->Sprite().getPosition().y);
			}
			if (this->_data->input.ClickedR(sf::Keyboard::Right))
			{
				gameState = GameStates::ePlaying;
				spaceShip->MoveR();
				laser->MoveR();
				this->_data->enetClient.SendMovementPacket(this->spaceShip->Sprite().getPosition().x, this->spaceShip->Sprite().getPosition().y);
			}
			if (this->_data->input.ClickedL(sf::Keyboard::Left))
			{
				gameState = GameStates::ePlaying;
				spaceShip->MoveL();
				laser->MoveL();
				this->_data->enetClient.SendMovementPacket(this->spaceShip->Sprite().getPosition().x, this->spaceShip->Sprite().getPosition().y);
			}
			if (this->_data->input.ClickedS(sf::Keyboard::Space))
			{
				gameState = GameStates::ePlaying;
				laser->SpawnLaser();
				this->_data->audio.Play("LaserSound.wav");
			}
		}
	}
}

void GameState::Update(float dt)
{
	fps->UpdateFPS();
	if (GameStates::ePlaying == gameState) 
	{
		asteroid->MoveAsteroid(dt);  // move asteroid method from asteroid class
		laser->MoveLaser(dt);

		if (clock.getElapsedTime().asSeconds() > spawnRate) // spawn asteroid based on the predefined clock frequency
		{
			asteroid->RandomiseAsteroid();
			asteroid->SpawnAsteroid();

			clock.restart();
		}
		spaceShip->Update(dt); // calling the update function from spaceShip class
		laser->Update(dt);
	}

	std::vector<sf::Sprite> asteroidprites = asteroid->GetSprites(); // same as above

	for (int i = 0; i < asteroidprites.size(); i++)
	{
		if (collision.SpriteCollision(spaceShip->Sprite(), asteroidprites.at(i)))
		{
			gameState = GameStates::eGameOver;
			this->_data->audio.Stop();
		}
	}

	/*                      bug contained...
	std::vector<sf::Sprite> LaserSprites = laser->GetSprites(); // same as above

	for (int i = 0; i < asteroidprites.size(); i++)
	{
		for (int j = 0; j < LaserSprites.size(); j++)
		{
			if (collision.SpriteCollision(LaserSprites.at(j), asteroidprites.at(i)))
			{
				asteroid->DeleteAsteroid();
				laser->DeleteLaser();
			}
		}
	}
	*/

	if (GameStates::eGameOver == gameState) //if the game state is set to over from the above loops
	{
		if (clock.getElapsedTime().asSeconds() > deathPause)
		{
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true); //we wait a predetermined time and push the maun menu state onto the stae machine
		}
	}
}

void GameState::Draw(float dt) // we draw everything from the game state
{
	this->_data->window.clear();
	this->_data->window.draw(this->background);

	asteroid->DrawAsteroid();
	laser->DrawLaser();
	spaceShip->Draw();
	fps->Draw();

	this->_data->window.display();
}
