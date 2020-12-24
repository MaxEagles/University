#pragma once
#include <SFML/Graphics.hpp>

bool button_clicked(sf::RectangleShape button, int x, int y)
{
	if (x > button.getPosition().x&& x<button.getSize().x + button.getPosition().x && y>button.getPosition().y&& y < button.getSize().y + button.getPosition().y)
	{
		return true;
	}
	return false;
}
