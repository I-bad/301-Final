#include "FPS.h"

FPS::FPS(GameDataRef data) : _data(data)
{
	Text.setFont(this->_data->assets.GetFont("Font")); //attributes of the string
	Text.setCharacterSize(24);
	Text.setPosition(sf::Vector2f(781, 0));
}

void FPS::Draw()
{
	_data->window.draw(Text);
}

void FPS::UpdateFPS()
{
	nowTime = clock.getElapsedTime(); // store the time it for a btween a frame
	fps = 1.0f / (nowTime.asSeconds() - previousTime.asSeconds()); // difference in time btween frame divided by 1 to get the fps 
	Text.setString(std::to_string(floor(fps))); //smfl function to store the float as a string 
	//std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
	previousTime = nowTime;
}