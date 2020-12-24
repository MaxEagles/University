#pragma once
#include <SFML/Graphics.hpp>
#include "Functions.h"

class Menu : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
public:
	bool active;
	Menu()
	{
		active = true;
		font.loadFromFile("font.ttf");
		button1.setSize(sf::Vector2f(500, 150));
		button2.setSize(sf::Vector2f(500, 150));
		button1.setPosition(710, 200);
		button2.setPosition(710, 500);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.clear(sf::Color::White);

		sf::RectangleShape shape(button1.getSize());
		sf::Text text("New game", font, 55);
		text.setFillColor(sf::Color::Black);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(-2);
		shape.setOutlineColor(sf::Color::Black);

		shape.setPosition(button1.getPosition());		
		target.draw(shape, states);
		text.setPosition(800, 240);
		target.draw(text, states);

		shape.setPosition(button2.getPosition());
		target.draw(shape, states);
		text.setPosition(900, 540);
		text.setString("Quit");
		target.draw(text, states);

		text.setPosition(900, 100);
		text.setString("Menu");
		target.draw(text, states);
	}

	int menu_choice(int x, int y)
	{
		if (button_clicked(button1, x, y))
		{
			return 1;
		}
		else if (button_clicked(button2, x, y))
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
};

class Menu2 : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::RectangleShape button1;
	sf::RectangleShape button2;
	sf::RectangleShape button3;
	sf::RectangleShape button4;
public:
	bool active;
	Menu2()
	{
		active = false;
		font.loadFromFile("font.ttf");
		button1.setSize(sf::Vector2f(500, 150));
		button2.setSize(sf::Vector2f(500, 150));
		button3.setSize(sf::Vector2f(500, 150));
		button4.setSize(sf::Vector2f(500, 150));
		button1.setPosition(710, 200);
		button2.setPosition(710, 400);
		button3.setPosition(710, 600);
		button4.setPosition(710, 800);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.clear(sf::Color::White);

		sf::RectangleShape shape(button1.getSize());
		sf::Text text("2", font, 55);
		text.setFillColor(sf::Color::Black);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(-2);
		shape.setOutlineColor(sf::Color::Black);

		shape.setPosition(button1.getPosition());
		target.draw(shape, states);
		text.setPosition(960, 240);
		target.draw(text, states);

		shape.setPosition(button2.getPosition());
		target.draw(shape, states);
		text.setPosition(960, 440);
		text.setString("3");
		target.draw(text, states);

		shape.setPosition(button3.getPosition());
		target.draw(shape, states);
		text.setPosition(960, 640);
		text.setString("4");
		target.draw(text, states);

		shape.setPosition(button4.getPosition());
		target.draw(shape, states);
		text.setPosition(960, 840);
		text.setString("5");
		target.draw(text, states);

		text.setPosition(900, 100);
		text.setString("Players:");
		target.draw(text, states);
	}

	int menu2_choice(int x, int y)
	{
		if (button_clicked(button1, x, y))
		{
			return 1;
		}
		else if (button_clicked(button2, x, y))
		{
			return 2;
		}
		else if (button_clicked(button3, x, y))
		{
			return 3;
		}
		else if (button_clicked(button4, x, y))
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}	
};
