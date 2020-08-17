#include "Engine.h"
#include "MainMenuState.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Engine::Engine(int width, int height, std::string title) //initialising the game - oppening the window and adding the initial state to the state machine
{
	_data->window.create(sf::VideoMode(width, height), title); // using the shared pointer to access the sf window function to create the window
	_data->machine.AddState(StateRef(new MainMenuState(this->_data)));
	this->Run();
}

void Engine::Run()
{
	this->_data->enetClient.connectToServer(1234); // run the connect to server function from our enet class
	
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds(); // amount of time that has passed since the clock began
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges(); // the first we thing we do is processing state changes/initialising a state
		this->_data->enetClient.listenToServer(); // runs the events from the enet library 

		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime; // how long it took between frames - handles differences in frame time 

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f; // restricting frame time difference so it does not get too high
		}

		currentTime = newTime; // current time is equal to the new time so we can check the difference between frame when we loop
		accumulator += frameTime; // totoal of all the frame times 

		while (accumulator >= dt) //while the time between frame is greater than our frame rate
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			accumulator -= dt; // resets the accum so we pop out the while loop
		}
		
		interpolation = accumulator / dt; // interpolation is used as a param to draw (dt)

		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
	this->_data->enetClient.destroyEnetClient();
}