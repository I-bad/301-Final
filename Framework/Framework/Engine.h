#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.h" //mamangers that will be accssed through the game data struct
#include "AssetManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "EnetClient.h"
#include "LevelEditor.h"


struct GameData // this will be accesible via all of the classes that include the engine
{
	StateMachine machine; //constains memebers of each portion of the game engine 
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
	AudioManager audio;
	EnetClient enetClient;
	LevelEditor levelEditor;
};

typedef std::shared_ptr<GameData> GameDataRef; // this pointer is what we will be suing when we access any of the managers above - shared pointer of type gamedata called game dataref

class Engine
{
public:
	Engine(int width, int height, std::string title); // game constructor - the engine itself

private:
	// this is what we actually use in different states to acces the game data stated above 
	//game data ref instance called _data
	GameDataRef _data = std::make_shared<GameData>();

	const float dt = 1.0f / 60.0f; // our frame rate - how much we update a second
	sf::Clock _clock; // clock for handling the frame rate

	void Run(); // method that gets called when we start our game (main game loop)
};
