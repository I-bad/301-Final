#include "Collision.h"

bool Collision::SpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{
	//rectangles around the sprites 
	sf::Rect<float> rect1 = sprite1.getGlobalBounds();
	sf::Rect<float> rect2 = sprite2.getGlobalBounds();

	//checking for collision using the intersect funtion
	if (rect1.intersects(rect2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
