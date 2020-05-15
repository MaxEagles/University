#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdlib.h>
#include <stdio.h>

struct sides
{
	int s_w = 1500;
	int s_h = 750;
	int t_w = 1200;
	int t_h = 600;
	int m_w = 400;
	int m_h = 70;
	int panel = 100;
	int l_side = s_w / 2 - t_w / 2;
	int r_side = s_w / 2 + t_w / 2;
	int d_side = panel + t_h;
};

struct rects
{
	SDL_Rect bg;
	SDL_Rect table;
	SDL_Rect s1;
	SDL_Rect s2;
	SDL_Rect rocket1;
	SDL_Rect rocket2;
	SDL_Rect ball;
	SDL_Rect new_gamee;
	SDL_Rect loadd;
	SDL_Rect aboutt;
	SDL_Rect quitt;
	SDL_Rect continuee;
	SDL_Rect menuu;
};

struct textures
{
	SDL_Texture* ballTexture;
	SDL_Texture* rocketTexture;
	SDL_Texture* bgTexture;
	SDL_Texture* new_gameeTexture;
	SDL_Texture* score1Texture;
	SDL_Texture* score2Texture;
	SDL_Texture* loaddTexture;
	SDL_Texture* abouttTexture;
	SDL_Texture* quittTexture;
	SDL_Texture* continueeTexture;
	SDL_Texture* menuuTexture;
	SDL_Texture* controlTexture;
	SDL_Texture* spaceTexture;
	SDL_Texture* nameTexture;
	SDL_Texture* overTexture;
};

struct ball
{
	int w = 30;
	int h = 30;
	int speed_x = 10;
	int speed_y = 0;
	int direction = 1;
};

struct rockets
{
	int w = 20;
	int h = 140;
	int speed1 = 0;
	int speed2 = 0;
	int speed = 10;
};

SDL_Texture* make_texture(SDL_Renderer*& renderer, const char* name, int color);
SDL_Texture* get_score_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font);
int menu(SDL_Renderer*& renderer, textures textures, rects rects);
int pause(SDL_Renderer*& renderer, textures textures, rects rects);
bool button_used(SDL_Rect rect, int x, int y);
int exit_game(rects rects, int score1, int score2, ball Ball);
void sound(Mix_Chunk* Sound);
void loadmusic(Mix_Music* fon);






