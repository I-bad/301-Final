#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"

class FPS
{
public:
	FPS(GameDataRef data);
	~FPS() {}

	void Draw();
	void UpdateFPS();

private:
	GameDataRef _data;

	sf::Text Text;

	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time nowTime;
};

