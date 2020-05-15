#include "Header.h"

int main(int argc, char** argv)
{
	int score1 = 0, score2 = 0;

	struct sides sides;
	struct rects rects;
	struct textures textures;
	struct ball Ball;
	struct rockets rockets;
	
	rects.bg = { 0,0,sides.s_w,sides.s_h };
	rects.table = { sides.l_side,sides.panel,sides.t_w,sides.t_h };
	rects.s1 = { sides.s_w / 2 - sides.panel - 20,10,sides.panel,sides.panel - 10 };
	rects.s2 = { sides.s_w / 2 + 20,10,sides.panel,sides.panel - 10 };
	rects.rocket1 = { sides.l_side,sides.panel + sides.t_h / 2 - rockets.h / 2,rockets.w,rockets.h };
	rects.rocket2 = { sides.r_side - rockets.w,sides.panel + sides.t_h / 2 - rockets.h / 2,rockets.w,rockets.h };
	rects.ball = { sides.s_w / 2,sides.t_h / 2 + sides.panel - Ball.h / 2,Ball.w,Ball.h };
	rects.new_gamee = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 6,sides.m_w, sides.m_h };
	rects.loadd = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 6 + 2 * sides.m_h,sides.m_w, sides.m_h };
	rects.aboutt = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 6 + 4 * sides.m_h,sides.m_w, sides.m_h };
	rects.quitt = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 6 + 6 * sides.m_h,sides.m_w, sides.m_h };
	rects.continuee = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 3,sides.m_w, sides.m_h };
	rects.menuu = { sides.s_w / 2 - sides.m_w / 2, sides.s_h / 3 * 2,sides.m_w, sides.m_h };

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tennis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sides.s_w, sides.s_h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	textures.ballTexture = make_texture(renderer, "ball.bmp", 255);
	textures.rocketTexture = make_texture(renderer, "rocket.bmp", 0);
	textures.bgTexture = make_texture(renderer, "bg.bmp", 100);
	textures.new_gameeTexture = make_texture(renderer, "new_gamee.bmp", 100);
	textures.loaddTexture = make_texture(renderer, "loadd.bmp", 100);
	textures.abouttTexture = make_texture(renderer, "aboutt.bmp", 100);
	textures.quittTexture = make_texture(renderer, "quitt.bmp", 100);
	textures.continueeTexture = make_texture(renderer, "continuee.bmp", 100);
	textures.menuuTexture = make_texture(renderer, "menuu.bmp", 100);
	textures.controlTexture = make_texture(renderer, "control.bmp", 100);
	textures.spaceTexture = make_texture(renderer, "space.bmp", 100);
	textures.nameTexture = make_texture(renderer, "name.bmp",100);
	textures.overTexture = make_texture(renderer, "over.bmp", 100);

	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Font.ttf", 100);
	char text1[10], text2[10];
	_itoa_s(score1, text1, 10);
	_itoa_s(score2, text2, 10);
	textures.score1Texture = get_score_texture(renderer, text1, my_font);
	textures.score2Texture = get_score_texture(renderer, text2, my_font);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;	
	
	switch (menu(renderer, textures, rects))
	{
		case 0: return 0;
		case 1: break;	
		case 2: 
		{
			FILE* file;
			fopen_s(&file, "C:\\Users\\Max\\Desktop\\настольный теннис\\настольный теннис\\exit.txt", "r");
			if (file == NULL)
			{
				printf("нет файла для загрузки игры\n");
				break;
			}
				
			fscanf_s(file, "%d", &score1);
			fscanf_s(file, "%d", &score2);
			fscanf_s(file, "%d", &rects.rocket1.y);
			fscanf_s(file, "%d", &rects.rocket2.y);
			fscanf_s(file, "%d", &rects.ball.x);
			fscanf_s(file, "%d", &rects.ball.y);
			fscanf_s(file, "%d", &Ball.direction);
			fscanf_s(file, "%d", &Ball.speed_x);
			fscanf_s(file, "%d", &Ball.speed_y);
			fclose(file);
			_itoa_s(score1, text1, 10);
			SDL_DestroyTexture(textures.score1Texture);
			textures.score1Texture = get_score_texture(renderer, text1, my_font);
			_itoa_s(score2, text2, 10);
			SDL_DestroyTexture(textures.score2Texture);
			textures.score2Texture = get_score_texture(renderer, text2, my_font);
		}break;	
		case 4: return 0;	
	}

	loadmusic(fon);
	
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit_game(rects, score1, score2, Ball);
				quit = true;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w))
			{
				rockets.speed1 = -rockets.speed;
			}
			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_w))
			{
				rockets.speed1 = 0;
			}

			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s))
			{
				rockets.speed1 = rockets.speed;
			}
			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_s))
			{
				rockets.speed1 = 0;
			}

			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_UP))
			{
				rockets.speed2 = -rockets.speed;
			}
			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_UP))
			{
				rockets.speed2 = 0;
			}

			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_DOWN))
			{
				rockets.speed2 = rockets.speed;
			}
			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_DOWN))
			{
				rockets.speed2 = 0;
			}		

			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
			{
				Mix_PauseMusic();				
				switch (pause(renderer, textures, rects))
				{					
					case 0: 
					{
						exit_game(rects, score1, score2, Ball);
						return 0;
					}
					case 1:Mix_ResumeMusic(); break;
					case 2:			
					{
						exit_game(rects, score1, score2, Ball);
						switch (menu(renderer, textures, rects))
						{
							case 0: return 0;
							case 1: 
							{
								score1 = score2 = 0;
								_itoa_s(score1, text1, 10);
								_itoa_s(score2, text2, 10);
								textures.score1Texture = get_score_texture(renderer, text1, my_font);
								textures.score2Texture = get_score_texture(renderer, text2, my_font);
								rects.rocket1.y = rects.rocket2.y = sides.panel + sides.t_h / 2 - rockets.h / 2;
								rects.ball.x = sides.s_w / 2;
								rects.ball.y = sides.t_h / 2 + sides.panel - Ball.h / 2;
								Ball.direction = 1;
								Ball.speed_x = 10;
								Ball.speed_y = 0;
								loadmusic(fon);
								break;
							}
							case 2: loadmusic(fon); break;
							case 4: return 0;						
						}
					}
				}
			}											
		}		

		//движение шарика
		int z01 = rects.rocket1.y - Ball.h / 4;
		int z11 = rects.rocket1.y + rockets.h / 5;
		int z12 = rects.rocket1.y + 2 * rockets.h / 5;
		int z13 = rects.rocket1.y + 3 * rockets.h / 5;
		int z14 = rects.rocket1.y + 4 * rockets.h / 5;
		int z15 = rects.rocket1.y + rockets.h + Ball.h / 4;
		int z02 = rects.rocket2.y - 3 * Ball.h / 4;
		int z21 = rects.rocket2.y + rockets.h / 5;
		int z22 = rects.rocket2.y + 2 * rockets.h / 5;
		int z23 = rects.rocket2.y + 3 * rockets.h / 5;
		int z24 = rects.rocket2.y + 4 * rockets.h / 5;
		int z25 = rects.rocket2.y + rockets.h + Ball.h / 4;
		int B_C = rects.ball.y + Ball.h / 2;
		rects.ball.x += Ball.speed_x * Ball.direction;
		rects.ball.y += Ball.speed_y;
		SDL_Delay(20);
		if (rects.ball.x <= sides.l_side + rockets.w && (B_C >= z01 && B_C < z11))
		{			
			sound(Sound);
			rects.ball.x = sides.l_side + rockets.w;
			Ball.direction = 1;
			Ball.speed_y = -10;
			Ball.speed_x += 1;
		}
		if (rects.ball.x <= sides.l_side + rockets.w && (B_C >= z11 && B_C < z12))
		{
			sound(Sound);
			rects.ball.x = sides.l_side + rockets.w;
			Ball.direction = 1;
			Ball.speed_y = -5;
			Ball.speed_x += 1;
		}
		if (rects.ball.x <= sides.l_side + rockets.w && (B_C >= z12 && B_C < z13))
		{			
			sound(Sound);
			rects.ball.x = sides.l_side + rockets.w;
			Ball.direction = 1;
			Ball.speed_x += 1;
		}
		if (rects.ball.x <= sides.l_side + rockets.w && (B_C >= z13 && B_C < z14))
		{			
			sound(Sound);
			rects.ball.x = sides.l_side + rockets.w;
			Ball.direction = 1;
			Ball.speed_y = 5;
			Ball.speed_x += 1;
		}
		if (rects.ball.x <= sides.l_side + rockets.w && (B_C >= z14 && B_C < z15))
		{			
			sound(Sound);
			rects.ball.x = sides.l_side + rockets.w;
			Ball.direction = 1;
			Ball.speed_y = 10;
			Ball.speed_x += 1;
		}

		if (rects.ball.x >= rects.rocket2.x - Ball.w && (B_C >= z02 && B_C < z21))
		{			
			sound(Sound);
			rects.ball.x = rects.rocket2.x - Ball.w;
			Ball.direction = -1;
			Ball.speed_y = -10;
			Ball.speed_x += 1;
		}
		if (rects.ball.x >= rects.rocket2.x - Ball.w && (B_C >= z21 && B_C < z22))
		{			
			sound(Sound);
			rects.ball.x = rects.rocket2.x - Ball.w;
			Ball.direction = -1;
			Ball.speed_y = -5;
			Ball.speed_x += 1;
		}
		if (rects.ball.x >= rects.rocket2.x - Ball.w && (B_C >= z22 && B_C < z23))
		{			
			sound(Sound);
			rects.ball.x = rects.rocket2.x - Ball.w;
			Ball.direction = -1;
			Ball.speed_x += 1;
		}
		if (rects.ball.x >= rects.rocket2.x - Ball.w && (B_C >= z23 && B_C < z24))
		{			
			sound(Sound);
			rects.ball.x = rects.rocket2.x - Ball.w;
			Ball.direction = -1;
			Ball.speed_y = 5;
			Ball.speed_x += 1;
		}
		if (rects.ball.x >= rects.rocket2.x - Ball.w && (B_C >= z24 && B_C < z25))
		{			
			sound(Sound);
			rects.ball.x = rects.rocket2.x - Ball.w;
			Ball.direction = -1;
			Ball.speed_y = 10;
			Ball.speed_x += 1;
		}

		if (rects.ball.x < sides.l_side - Ball.w)
		{
			SDL_Delay(1000);
			rects.ball.x = sides.s_w / 2;
			rects.ball.y = sides.t_h / 2 + sides.panel - Ball.h / 2;
			rects.rocket1.y = sides.t_h / 2 - rockets.h / 2 + sides.panel;
			rects.rocket2.y = sides.t_h / 2 - rockets.h / 2 + sides.panel;
			Ball.speed_y = 0;
			Ball.speed_x = 10;
			score2++;
			_itoa_s(score2, text2, 10);
			SDL_DestroyTexture(textures.score2Texture);
			textures.score2Texture = get_score_texture(renderer, text2, my_font);
		}

		if (rects.ball.x > sides.r_side)
		{
			SDL_Delay(1000);
			rects.ball.x = sides.s_w / 2;
			rects.ball.y = sides.t_h / 2 + sides.panel - Ball.h / 2;
			rects.rocket1.y = sides.t_h / 2 - rockets.h / 2 + sides.panel;
			rects.rocket2.y = sides.t_h / 2 - rockets.h / 2 + sides.panel;
			Ball.speed_y = 0;
			Ball.speed_x = 10;
			score1++;
			_itoa_s(score1, text1, 10);
			SDL_DestroyTexture(textures.score1Texture);
			textures.score1Texture = get_score_texture(renderer, text1, my_font);
		}

		if (rects.ball.y <= sides.panel || rects.ball.y >= sides.d_side - Ball.h)
		{			
			sound(Sound);
			Ball.speed_y *= -1;
		}

		//движение ракеток
		rects.rocket1.y += rockets.speed1;
		rects.rocket2.y += rockets.speed2;
		if (rects.rocket1.y <= sides.panel)
			rects.rocket1.y = sides.panel + 1;
		if (rects.rocket2.y <= sides.panel)
			rects.rocket2.y = sides.panel + 1;
		if (rects.rocket1.y > sides.d_side - rockets.h)
			rects.rocket1.y = sides.d_side - rockets.h;
		if (rects.rocket2.y > sides.d_side - rockets.h)
			rects.rocket2.y = sides.d_side - rockets.h;

		//конец игры
		if (score1 == 10 || score2 == 10)
		{
			score1 = 0;
			score2 = 0;
			_itoa_s(score1, text1, 10);
			SDL_DestroyTexture(textures.score1Texture);
			textures.score1Texture = get_score_texture(renderer, text1, my_font);
			_itoa_s(score2, text2, 10);
			SDL_DestroyTexture(textures.score2Texture);
			textures.score2Texture = get_score_texture(renderer, text2, my_font);
			SDL_RenderCopy(renderer, textures.overTexture, NULL, &rects.bg);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);
			Mix_PauseMusic();
			switch (pause(renderer, textures, rects))
			{
				case 0:	return 0;				
				case 1: Mix_ResumeMusic(); break;
				case 2:
				{
					switch (menu(renderer, textures, rects))
					{
					case 0: return 0;
					case 1: loadmusic(fon);	break;				
					case 2: loadmusic(fon); break;
					case 4: return 0;
					}
				}
			}			
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textures.bgTexture, NULL, &rects.bg);
		SDL_RenderFillRect(renderer, &rects.table);
		SDL_RenderCopy(renderer, textures.score1Texture, NULL, &rects.s1);
		SDL_RenderCopy(renderer, textures.score2Texture, NULL, &rects.s2);
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
		SDL_RenderDrawRect(renderer, &rects.table);
		SDL_RenderDrawLine(renderer, sides.s_w / 2, 0, sides.s_w / 2, sides.d_side);
		SDL_RenderCopy(renderer, textures.ballTexture, NULL, &rects.ball);
		SDL_RenderCopy(renderer, textures.rocketTexture, NULL, &rects.rocket1);
		SDL_RenderCopy(renderer, textures.rocketTexture, NULL, &rects.rocket2);
		SDL_RenderPresent(renderer);
	}
	
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	SDL_DestroyTexture(textures.spaceTexture);
	SDL_DestroyTexture(textures.controlTexture);
	SDL_DestroyTexture(textures.menuuTexture);
	SDL_DestroyTexture(textures.continueeTexture);
	SDL_DestroyTexture(textures.quittTexture);
	SDL_DestroyTexture(textures.abouttTexture);
	SDL_DestroyTexture(textures.loaddTexture);
	SDL_DestroyTexture(textures.score1Texture);
	SDL_DestroyTexture(textures.score2Texture);
	SDL_DestroyTexture(textures.new_gameeTexture);
	SDL_DestroyTexture(textures.bgTexture);
	SDL_DestroyTexture(textures.rocketTexture);
	SDL_DestroyTexture(textures.ballTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}



