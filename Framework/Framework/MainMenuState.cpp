#pragma once
#include <iostream>
#include <sstream>
#include "MainMenuState.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data) // contrscutor with the parameter of game data ref and it is automatically assigned to data refernce in our class
{
}

void MainMenuState::Init()
{
	this->_data->audio.Init(); // audio system function for initialising FMod/studio system then loading and play the select file
	this->_data->audio.Play("music.wav");

	// here we are cimply casting the values we return from the specifed file from our level editor 
	lua_State* F = this->_data->levelEditor.setupLuaFile("level.lua");
	LuaRef w = this->_data->levelEditor.getLuaStackProperty(F, "directories", "Background");
	LuaRef p = this->_data->levelEditor.getLuaStackProperty(F, "directories", "PlayButton");

	//asset manager functions which load and store what we need and then using the get texture function to set it from the map data
	this->_data->assets.LoadTexture("Background", w); // loading texture with assetmanager
	this->_data->assets.LoadTexture("Play Button", p);
	backGround.setTexture(this->_data->assets.GetTexture("Background")); //setting texture to our background sprite
	playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
	playButton.setPosition((800 / 2) - (playButton.getGlobalBounds().width / 2), (850 / 2) - (playButton.getGlobalBounds().height / 2));
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		// usuing the spriteclicked method from the input manager, we pass in the sprite we check for a click and the window all this belongs to.
		if (this->_data->input.IsSpriteClicked(this->playButton, sf::Mouse::Left, this->_data->window))
		{
			//add the agme state to the state machine stack
			this->_data->machine.AddState(StateRef(new GameState(_data)), true);
		}
	}
}

void MainMenuState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(this->backGround); // rendering everything we specified
	this->_data->window.draw(this->playButton);

	this->_data->window.display();
}
