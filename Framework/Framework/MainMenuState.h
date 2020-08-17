#pragma once
#include <SFML/Graphics.hpp>
#include "State.h" 
#include "Engine.h"
#include "GameState.h"

class MainMenuState : public State // main menu class which is a memeber the state class // inherits from the sstate calss
{
public:
	MainMenuState(GameDataRef data);// constructor which takes the game data ref from the engine class

	void Init();
	void HandleInput();
	void Update(float dt) {}
	void Draw(float dt);

private:
	GameDataRef _data; // local refernce for the game data for the windows and input state etc..

	sf::Sprite backGround; 
	sf::Sprite playButton;
};
