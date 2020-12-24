#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"

#define CELLS_N 7
#define CELL_SIZE 150

class Cell
{
public:
	sf::RectangleShape shape;
	int value;
	Hero* hero;
	Cell()
	{
		shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		shape.setOutlineThickness(-2);
		shape.setOutlineColor(sf::Color::Black);
		shape.setFillColor(sf::Color::White);
		hero = NULL;
	}
};
