#pragma once

#include "SFML\Graphics.hpp"

//the input system enamables functions that we can call for the different smfl events which we will use for the different states
class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

	//this method will be used to check if a certain sprite is clicked and we can implement this whereever
	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window); 
		
	//these methods handles keyboard inputs respectively and again we can call these to any state
	bool ClickedU(sf::Keyboard::Key key);
	bool ClickedD(sf::Keyboard::Key key);
	bool ClickedR(sf::Keyboard::Key key);
	bool ClickedL(sf::Keyboard::Key key);
	bool ClickedS(sf::Keyboard::Key key);
};
