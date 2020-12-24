#pragma once
#include <SFML/Graphics.hpp>

class Hero
{
public:
	sf::RectangleShape shape;
	Hero()
	{
		shape.setSize(sf::Vector2f(100, 100));		
		shape.setOutlineColor(sf::Color::Transparent);
		shape.setOutlineThickness(-2);
		shape.setFillColor(sf::Color::White);
	}
	int position1;
	int position2;	
	int penalty;
	int score;
};
