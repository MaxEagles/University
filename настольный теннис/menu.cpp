#include "Header.h"

int menu(SDL_Renderer*& renderer, textures textures, rects rects)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures.spaceTexture, NULL, &rects.bg);
	SDL_RenderCopy(renderer, textures.nameTexture, NULL, &rects.bg);
	SDL_RenderCopy(renderer, textures.new_gameeTexture, NULL, &rects.new_gamee);
	SDL_RenderCopy(renderer, textures.loaddTexture, NULL, &rects.loadd);
	SDL_RenderCopy(renderer, textures.abouttTexture, NULL, &rects.aboutt);
	SDL_RenderCopy(renderer, textures.quittTexture, NULL, &rects.quitt);
	SDL_RenderPresent(renderer);
	SDL_Event event;
	bool quit_menu = false;
	while (!quit_menu)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return 0;
				quit_menu = true;				
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{
				if (button_used(rects.new_gamee, event.button.x, event.button.y))
				{
					return 1;
					quit_menu = true;
				}

				if (button_used(rects.loadd, event.button.x, event.button.y))
				{
					return 2;
					quit_menu = true;
				}

				if (button_used(rects.aboutt, event.button.x, event.button.y))
				{		
					SDL_RenderCopy(renderer, textures.spaceTexture, NULL, &rects.bg);
					SDL_RenderCopy(renderer, textures.nameTexture, NULL, &rects.bg);
					SDL_RenderCopy(renderer, textures.controlTexture, NULL, &rects.bg);
					SDL_RenderCopy(renderer, textures.menuuTexture, NULL, &rects.menuu);
					SDL_RenderPresent(renderer);
					SDL_Event event;
					bool quit_about = false;
					while (!quit_about)
					{
						while (SDL_PollEvent(&event))
						{
							if (event.type == SDL_QUIT)
							{
								return 0;
							}
							if (event.type == SDL_MOUSEBUTTONDOWN &&
								event.button.button == SDL_BUTTON_LEFT)
							{
								if (button_used(rects.menuu, event.button.x, event.button.y))
								{
									quit_about = true;
									SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
									SDL_RenderCopy(renderer, textures.nameTexture, NULL, &rects.bg);
									SDL_RenderClear(renderer);
									SDL_RenderCopy(renderer, textures.spaceTexture, NULL, &rects.bg);
									SDL_RenderCopy(renderer, textures.nameTexture, NULL, &rects.bg);
									SDL_RenderCopy(renderer, textures.new_gameeTexture, NULL, &rects.new_gamee);
									SDL_RenderCopy(renderer, textures.loaddTexture, NULL, &rects.loadd);
									SDL_RenderCopy(renderer, textures.abouttTexture, NULL, &rects.aboutt);
									SDL_RenderCopy(renderer, textures.quittTexture, NULL, &rects.quitt);
									SDL_RenderPresent(renderer);
								}
							}
						}						
					}
				}

				if (button_used(rects.quitt, event.button.x, event.button.y))
				{
					return 4;
					quit_menu = true;
				}
			}
		}
	}
}


int pause(SDL_Renderer*& renderer, textures textures, rects rects)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures.spaceTexture, NULL, &rects.bg);
	SDL_RenderCopy(renderer, textures.nameTexture, NULL, &rects.bg);
	SDL_RenderCopy(renderer, textures.continueeTexture, NULL, &rects.continuee);
	SDL_RenderCopy(renderer, textures.menuuTexture, NULL, &rects.menuu);
	SDL_RenderPresent(renderer);
	SDL_Event event;
	bool quit_pause = false;
	while (!quit_pause)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit_pause = true;
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN &&
				event.button.button == SDL_BUTTON_LEFT)
			{
				if (button_used(rects.continuee, event.button.x, event.button.y))
				{
					return 1;
					quit_pause = true;
				}
				
				if (button_used(rects.menuu, event.button.x, event.button.y))
				{
					return 2;
					quit_pause = true;
				}

			}
		}
	}
}