#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Cell.h"
#include "Card.h"
#include "Hero.h"
#include "Player.h"
#include "Functions.h"
using namespace std;


class Game : public sf::Drawable, public sf::Transformable
{
private:		
	sf::Texture v1_texture;
	sf::Texture v2_texture;
	sf::Texture v3_texture;
	sf::Texture v4_texture;
	sf::Texture boss_texture;
	sf::Texture hero_textures[5];

	sf::Texture table_texture;
	sf::Sprite table_sprite;
	sf::Texture wall_texture;
	sf::Sprite wall1_sprite;
	sf::Sprite wall2_sprite;
	sf::Sprite wall3_sprite;

	sf::RectangleShape cards[3];	

	sf::Font font;

	Cell cells[CELLS_N][CELLS_N];
public:
	sf::RectangleShape end_turn;
	int n;
	Hero* heroes;
	Player* players;
	bool active;
	bool is_push;
	int active_player;
	Hero* pushing;
	Card* active_card;
	int books;
	Game()
	{
		font.loadFromFile("font.ttf");

		active = false;
		cells[0][0].value = cells[0][1].value = cells[0][4].value = cells[2][2].value = cells[2][6].value = cells[4][0].value = cells[4][1].value = cells[4][5].value = cells[6][2].value = cells[6][3].value = cells[6][6].value
			= 1;
		cells[0][2].value = cells[0][3].value = cells[2][0].value = cells[2][1].value = cells[2][4].value = cells[2][5].value = cells[4][3].value = cells[4][6].value = cells[6][0].value = cells[6][1].value = cells[6][4].value = cells[6][5].value
			= 2;
		cells[1][1].value = cells[1][2].value = cells[3][3].value = cells[3][4].value = cells[3][0].value = cells[5][1].value = cells[5][5].value = cells[5][6].value
			= 3;
		cells[1][0].value = cells[1][4].value = cells[3][1].value = cells[3][2].value = cells[3][5].value = cells[3][6].value = cells[5][0].value = cells[5][3].value
			= 4;
		cells[1][3].value = cells[2][3].value = cells[4][2].value = cells[4][4].value = cells[5][2].value = cells[5][4].value
			= 5;
		cells[0][5].value = cells[0][6].value = cells[1][5].value = cells[1][6].value
			= 0;

		v1_texture.loadFromFile("red.png");
		v2_texture.loadFromFile("green.png");
		v3_texture.loadFromFile("blue.png");
		v4_texture.loadFromFile("yellow.png");
		boss_texture.loadFromFile("boss.jpg");
		hero_textures[0].loadFromFile("hero1.jpg");
		hero_textures[1].loadFromFile("hero2.jpg");
		hero_textures[2].loadFromFile("hero3.jpg");
		hero_textures[3].loadFromFile("hero4.jpg");
		hero_textures[4].loadFromFile("hero5.jpg");	
		table_texture.loadFromFile("table.jpg");		
		table_sprite.setTexture(table_texture);	
		wall_texture.loadFromFile("wall.png");
		wall1_sprite.setTexture(wall_texture);
		wall2_sprite.setTexture(wall_texture);
		wall3_sprite.setTexture(wall_texture);

		for (int i = 0; i < CELLS_N; i++)
		{
			for (int j = 0; j < CELLS_N; j++)
			{
				cells[i][j].shape.setPosition(j * CELL_SIZE, i * CELL_SIZE);
			}
		}	

		table_sprite.setPosition(cells[0][5].shape.getPosition());
		wall1_sprite.setPosition(cells[1][3].shape.getPosition());
		wall2_sprite.setPosition(cells[4][2].shape.getPosition());
		wall3_sprite.setPosition(cells[4][4].shape.getPosition());
		

		for (int i = 0; i < 3; i++)
		{
			cards[i].setSize(sf::Vector2f(300, 300));
			cards[i].setPosition(1100, 100 + i * 330);
			cards[i].setOutlineColor(sf::Color::Black);
			cards[i].setOutlineThickness(-2);
		}

		end_turn.setSize(sf::Vector2f(400, 200));
		end_turn.setPosition(1500, 800);
		end_turn.setOutlineColor(sf::Color::Black);
		end_turn.setOutlineThickness(-2);
		end_turn.setFillColor(sf::Color::Transparent);
		
	}
	void Init(int N)
	{
		books = 15;
		is_push = false;
		pushing = NULL;
		n = N;
		heroes = new Hero[n + 1];
		players = new Player[n];
		heroes[n].position1 = 0;
		heroes[n].position2 = 3;
		cells[0][3].hero = &heroes[n];
		heroes[n].shape.setTexture(&boss_texture);
		for (int i = 0; i < n; i++)
		{
			heroes[i].position1 = 6;
			heroes[i].position2 = i;
			cells[6][i].hero = &heroes[i];
			heroes[i].shape.setTexture(&hero_textures[i]);	
			heroes[i].penalty = 0;
			heroes[i].score = 0;
		}

		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				players[i].cards[j].value1 = rand() % 4 + 1;
				players[i].cards[j].value2 = rand() % 4 + 1;
				players[i].cards[j].value3 = rand() % 4 + 1;
			}
		}

		active_player = 0;
		active_card = NULL;
	}	

	~Game()
	{
		delete[] heroes;
		delete[] players;
	}

	void new_card(Card* c)
	{
		srand(time(NULL));
		c->value1 = rand() % 4 + 1;
		c->value2 = rand() % 4 + 1;	
		c->value3 = rand() % 4 + 1;
	}	

	void push(int p1, int p2, Hero* h)
	{		
		if (cells[p1][p2].value < 5)
		{
			if (((h->position1 == p1 - 1 || h->position1 == p1 + 1) && h->position2 == p2) || (h->position2 == p2 - 1 || h->position2 == p2 + 1) && h->position1 == p1)
			{				
				if (cells[p1][p2].hero != NULL)
				{
					is_push = true;					
					pushing = cells[p1][p2].hero;					
					cells[p1][p2].hero->shape.setOutlineColor(sf::Color::Red);
				}
				else
				{
					is_push = false;
					pushing = NULL;					
				}
				h->position1 = p1;
				h->position2 = p2;
				cells[h->position1][h->position2].hero = NULL;
				cells[p1][p2].hero = h;	
				h->shape.setOutlineColor(sf::Color::Transparent);
				heroes[active_player].shape.setFillColor(sf::Color::White);
			}
		}
	}

	void step_boss(int p1, int p2, int value)
	{
		if (active_card->value1 == value)
		{
			if (((heroes[n].position1 == p1 - 1 || heroes[n].position1 == p1 + 1) && heroes[n].position2 == p2) || ((heroes[n].position2 == p2 - 1 || heroes[n].position2 == p2 + 1) && heroes[n].position1 == p1))
			{
				if (cells[p1][p2].hero != NULL)
				{
					cells[p1][p2].hero->position1 = 6;
					cells[p1][p2].hero->position2 = 0;
					cells[p1][p2].hero->penalty++;
					cells[6][0].hero = cells[p1][p2].hero;
					cells[p1][p2].hero = NULL;
				}
				cells[heroes[n].position1][heroes[n].position2].hero = NULL;
				heroes[n].position1 = p1;
				heroes[n].position2 = p2;
				cells[p1][p2].hero = &heroes[n];
				active_card->value1 = 0;				
			}
		}

		if (active_card->value2 == value)
		{
			if (((heroes[n].position1 == p1 - 1 || heroes[n].position1 == p1 + 1) && heroes[n].position2 == p2) || ((heroes[n].position2 == p2 - 1 || heroes[n].position2 == p2 + 1) && heroes[n].position1 == p1))
			{
				if (cells[p1][p2].hero != NULL)
				{
					cells[p1][p2].hero->position1 = 6;
					cells[p1][p2].hero->position2 = 0;
					cells[p1][p2].hero->penalty++;
					cells[6][0].hero = cells[p1][p2].hero;
					cells[p1][p2].hero = NULL;
				}
				cells[heroes[n].position1][heroes[n].position2].hero = NULL;
				heroes[n].position1 = p1;
				heroes[n].position2 = p2;
				cells[p1][p2].hero = &heroes[n];
				active_card->value2 = 0;			
			}
		}
	}

	void step(int p1, int p2, int value)
	{
		if (value == 0)
		{
			if (((heroes[active_player].position1 == p1 - 1 || heroes[active_player].position1 == p1 + 1) && heroes[active_player].position2 == p2) || ((heroes[active_player].position2 == p2 - 1 || heroes[active_player].position2 == p2 + 1) && heroes[active_player].position1 == p1))
			{
				srand(time(NULL));
				cells[heroes[active_player].position1][heroes[active_player].position2].hero = NULL;
				heroes[active_player].position1 = 6;
				heroes[active_player].position2 = 0;
				heroes[active_player].score += rand() % 3 + 1;
				books--;
				cells[6][0].hero = &heroes[active_player];
				active_card->value1 = 0;
				active_card->value2 = 0;
			}
		}

		if (active_card->value1 == value)
		{			
			if(((heroes[active_player].position1 == p1 - 1 || heroes[active_player].position1 == p1 + 1) && heroes[active_player].position2 == p2) || ((heroes[active_player].position2 == p2 - 1 || heroes[active_player].position2 == p2 + 1) && heroes[active_player].position1 == p1))
			{
				bool punished = false;
				if (cells[p1][p2].hero != NULL)
				{
					if (cells[p1][p2].hero->position1 == heroes[n].position1 && cells[p1][p2].hero->position2 == heroes[n].position2)
					{
						heroes[active_player].penalty++;
						punished = true;
					}
					else
					{
						is_push = true;
						pushing = cells[p1][p2].hero;
						heroes[active_player].shape.setFillColor(sf::Color::Transparent);
						cells[p1][p2].hero->shape.setOutlineColor(sf::Color::Red);
					}
				}
				if (punished)
				{
					cells[heroes[active_player].position1][heroes[active_player].position2].hero = NULL;
					heroes[active_player].position1 = 6;
					heroes[active_player].position2 = 0;
					cells[6][0].hero = &heroes[active_player];
					active_card->value1 = 0;
					active_card->value2 = 0;
				}
				else
				{
					cells[heroes[active_player].position1][heroes[active_player].position2].hero = NULL;
					heroes[active_player].position1 = p1;
					heroes[active_player].position2 = p2;
					cells[p1][p2].hero = &heroes[active_player];
					active_card->value1 = 0;
				}
			}
		}	

		if (active_card->value2 == value)
		{			
			if (((heroes[active_player].position1 == p1 - 1 || heroes[active_player].position1 == p1 + 1) && heroes[active_player].position2 == p2) || ((heroes[active_player].position2 == p2 - 1 || heroes[active_player].position2 == p2 + 1) && heroes[active_player].position1 == p1))
			{
				bool punished = false;
				if (cells[p1][p2].hero != NULL)
				{
					if (cells[p1][p2].hero->position1 == heroes[n].position1 && cells[p1][p2].hero->position2 == heroes[n].position2)
					{
						heroes[active_player].penalty++;
						punished = true;
					}
					else
					{
						is_push = true;
						pushing = cells[p1][p2].hero;
						heroes[active_player].shape.setFillColor(sf::Color::Transparent);
						cells[p1][p2].hero->shape.setOutlineColor(sf::Color::Red);
					}
				}
				if (punished)
				{
					cells[heroes[active_player].position1][heroes[active_player].position2].hero = NULL;
					heroes[active_player].position1 = 6;
					heroes[active_player].position2 = 0;
					cells[6][0].hero = &heroes[active_player];
					active_card->value1 = 0;
					active_card->value2 = 0;
				}
				else
				{
					cells[heroes[active_player].position1][heroes[active_player].position2].hero = NULL;
					heroes[active_player].position1 = p1;
					heroes[active_player].position2 = p2;
					cells[p1][p2].hero = &heroes[active_player];
					active_card->value2 = 0;
				}
			}
		}
	}

	void game_choice(int x, int y)
	{
		for (int i = 0; i < CELLS_N; i++)
		{
			for (int j = 0; j < CELLS_N; j++)
			{
				if (is_push && button_clicked(cells[i][j].shape, x, y))
				{
					push(i, j, pushing);
				}
				else if (active_card != NULL && active_card->value3 == 1 && button_clicked(cells[i][j].shape, x, y))
				{
					step_boss(i, j, cells[i][j].value);
				}
				else if (active_card != NULL && button_clicked(cells[i][j].shape, x, y))
				{										
					step(i, j, cells[i][j].value);
				}
			}
		}

		if (button_clicked(cards[0], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &players[active_player].cards[0];
				cards[0].setOutlineColor(sf::Color::Red);
			}			
		}
		else if (button_clicked(cards[1], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &players[active_player].cards[1];
				cards[1].setOutlineColor(sf::Color::Red);
			}
		}
		else if (button_clicked(cards[2], x, y))
		{
			if (active_card == NULL)
			{
				active_card = &players[active_player].cards[2];
				cards[2].setOutlineColor(sf::Color::Red);
			}
		}
		else if (button_clicked(end_turn, x, y))
		{
			if (active_card != NULL)
			{
				new_card(active_card);
				active_card = NULL;
				for (int i = 0; i < 3; i++)
				{
					cards[i].setOutlineColor(sf::Color::Black);
				}
			}
			if (active_player != n-1)
			{
				active_player++;
			}
			else
			{
				active_player = 0;
			}
		}	
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		draw_field(target, states);
		draw_heroes(target, states);
		draw_cards(target, states, active_player);
		draw_end(target, states);
	}

	void draw_field(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();		

		sf::RectangleShape value_shape(sf::Vector2f(CELL_SIZE / 4, CELL_SIZE / 4));
		value_shape.setFillColor(sf::Color::White);
		for (int i = 0; i < CELLS_N; i++)
		{
			for (int j = 0; j < CELLS_N; j++)
			{
				target.draw(cells[i][j].shape, states);
				value_shape.setPosition(cells[i][j].shape.getPosition().x+10, cells[i][j].shape.getPosition().y + 10);
				if (cells[i][j].value == 1)
				{						
					value_shape.setTexture(&v1_texture);				
					target.draw(value_shape, states);
					
				}
				if (cells[i][j].value == 2)
				{
					value_shape.setTexture(&v2_texture);
					target.draw(value_shape, states);
				}
				if (cells[i][j].value == 3)
				{
					value_shape.setTexture(&v3_texture);
					target.draw(value_shape, states);
				}
				if (cells[i][j].value == 4)
				{
					value_shape.setTexture(&v4_texture);
					target.draw(value_shape, states);
				}
			}
		}	

		target.draw(table_sprite, states);
		target.draw(wall1_sprite, states);
		target.draw(wall2_sprite, states);
		target.draw(wall3_sprite, states);

		sf::Text text("", font, 55);
		text.setString(std::to_string(books));
		text.setPosition(100, 100);

	}

	void draw_heroes(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (int i = 0; i < n + 1; i++)
		{
			heroes[i].shape.setPosition(cells[heroes[i].position1][heroes[i].position2].shape.getPosition().x + 45, cells[heroes[i].position1][heroes[i].position2].shape.getPosition().y + 45);
			target.draw(heroes[i].shape, states);
		}
	}

	void draw_end(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		sf::Text text("End turn", font, 55);
		text.setFillColor(sf::Color::Black);
		sf::Text score("", font, 55);
		sf::Text penalty("", font, 55);
		score.setFillColor(sf::Color::Green);
		penalty.setFillColor(sf::Color::Red);
		score.setPosition(1500, 100);
		penalty.setPosition(1550, 100);

		sf::RectangleShape shape(end_turn);

		switch (active_player)
		{
		case 0: shape.setFillColor(sf::Color::Red); break;
		case 1: shape.setFillColor(sf::Color::Green); break;
		case 2: shape.setFillColor(sf::Color::Blue); break;
		case 3: shape.setFillColor(sf::Color::Yellow); break;
		case 4: shape.setFillColor(sf::Color::Magenta); break;
		default:break;
		}

		score.setString(std::to_string(heroes[active_player].score));
		penalty.setString(std::to_string(heroes[active_player].penalty));
		target.draw(score, states);
		target.draw(penalty, states);

		text.setPosition(1600, 840);
		target.draw(shape, states);
		target.draw(text, states);
		target.draw(end_turn, states);
	}

	void draw_cards(sf::RenderTarget& target, sf::RenderStates states, int p) const
	{
		states.transform *= getTransform();	

		sf::RectangleShape value_shape(sf::Vector2f(75, 75));
		value_shape.setFillColor(sf::Color::White);
		for (int i = 0; i < 3; i++)
		{
			target.draw(cards[i], states);			

			value_shape.setPosition(cards[i].getPosition());
			if (players[p].cards[i].value3 == 1)
			{
				sf::RectangleShape shape(sf::Vector2f(296, 296));
				shape.setFillColor(sf::Color::Black);
				shape.setPosition(cards[i].getPosition().x + 2, cards[i].getPosition().y + 2);
				target.draw(shape, states);
			}
			if (players[p].cards[i].value1 == 1)
			{
				value_shape.setTexture(&v1_texture);
				target.draw(value_shape, states);

			}
			if (players[p].cards[i].value1 == 2)
			{
				value_shape.setTexture(&v2_texture);
				target.draw(value_shape, states);
			}
			if (players[p].cards[i].value1 == 3)
			{
				value_shape.setTexture(&v3_texture);
				target.draw(value_shape, states);
			}
			if (players[p].cards[i].value1 == 4)
			{
				value_shape.setTexture(&v4_texture);
				target.draw(value_shape, states);
			}

			value_shape.setPosition(cards[i].getPosition().x+225, cards[i].getPosition().y);
			if (players[p].cards[i].value2 == 1)
			{
				value_shape.setTexture(&v1_texture);
				target.draw(value_shape, states);

			}
			if (players[p].cards[i].value2 == 2)
			{
				value_shape.setTexture(&v2_texture);
				target.draw(value_shape, states);
			}
			if (players[p].cards[i].value2 == 3)
			{
				value_shape.setTexture(&v3_texture);
				target.draw(value_shape, states);
			}
			if (players[p].cards[i].value2 == 4)
			{
				value_shape.setTexture(&v4_texture);
				target.draw(value_shape, states);
			}
		}
	}
};
