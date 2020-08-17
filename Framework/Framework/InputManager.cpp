#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(button)) // detect if the mouse button that is being passed is is pressed
	{
		//here we create a rectangle called playbttn  and get its size by the object passed in
		sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (playButtonRect.contains(sf::Mouse::getPosition(window))) //detect if rect has the clicked within its bound
		{
				return true;
		}
	}
	return false;
}

bool InputManager::ClickedU(sf::Keyboard::Key key) 
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
}
bool InputManager::ClickedD(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
}
bool InputManager::ClickedR(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
}
bool InputManager::ClickedL(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
}
bool InputManager::ClickedS(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
}

