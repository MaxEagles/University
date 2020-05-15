#include "Header.h"

SDL_Texture* make_texture(SDL_Renderer*& renderer, const char* name, int color)
{
	SDL_Surface* Image = IMG_Load(name);
	SDL_SetColorKey(Image, SDL_TRUE,
		SDL_MapRGB(Image->format, color, color, color));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Image);
	SDL_FreeSurface(Image);
	return texture;
}

SDL_Texture* get_score_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* scoreSurface = NULL;
	SDL_Color fore_color = { 0,255,255 };
	SDL_Color back_color = { 32,0,64 };
	scoreSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface);
	return texture;
}

bool button_used(SDL_Rect rect, int x, int y)
{
	bool a = false;
	if ((x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y < rect.y + rect.h))
		a = true;
	return a;
}

int exit_game(rects rects, int score1, int score2, ball Ball)
{
	FILE* file;
	fopen_s(&file, "C:\\Users\\Max\\Desktop\\настольный теннис\\настольный теннис\\exit.txt", "w");
	if (file == NULL)
		return 1;
	fprintf(file, "%d %d %d %d %d %d %d %d %d", score1, score2, rects.rocket1.y, rects.rocket2.y, rects.ball.x, rects.ball.y, Ball.direction, Ball.speed_x, Ball.speed_y);
	fclose(file);
}

void sound(Mix_Chunk* Sound)
{
	Sound = Mix_LoadWAV("kick.wav");
	Mix_PlayChannel(-1, Sound, 0);
}

void loadmusic(Mix_Music* fon)
{
	fon = Mix_LoadMUS("song.mp3");
	Mix_PlayMusic(fon, -1);
}
