#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Game.h"

int main(int argc, char** argv) {
	int t1, t2, quit, frames, rc;
	double delta, fpsTimer, distance;
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Surface* texts;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	printf("printf output goes here\n");


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	//init sdl_image
	//if (!(IMG_Init(IMG_INIT_PNG)))
	//	printf("Png files cannot be loaded!");

	Game* game = new Game(renderer);
	game->draw->screen = screen;

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	fpsTimer = 0;
	quit = 0;
	frames = 0;

	while (!quit) {

		if (game->error)
		{
			SDL_FreeSurface(screen);
			SDL_DestroyTexture(scrtex);
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			return 1;
		}

		t2 = SDL_GetTicks();

		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		game->worldTime += delta;

		//clear screen
		
		//game->draw->DrawSurface(screen, game->draw->background, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		

		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			game->fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		//// tekst informacyjny / info text
		game->draw->DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//"template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", game->worldTime, game->fps);
		//game->draw->DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, game->draw->charset, 8);


		////"Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "GH8I7");
		//game->draw->DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, game->draw->charset, 8);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = SCREEN_WIDTH;
		rect.h = SCREEN_HEIGHT - 200;


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_FillRect(screen, NULL, 0x000000);

		game->draw->drawPartOfTexture(renderer, game->draw->background, 0, 100, rect, 0, SDL_FLIP_NONE);
		game->play();

		
		SDL_RenderPresent(renderer);
		

		// handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;

				if (event.key.keysym.sym == SDLK_p)
					game->paused = !game->paused;
				else if(!game->paused)
					game->frog->jump(event.key.keysym.sym);
				
				if (event.key.keysym.sym == SDLK_q)
				{
					if (game->over)
						quit = 1;
					
					if (!game->endGameAsk)
						game->endGameAsk = true;
				}

				if (event.key.keysym.sym == SDLK_y)
				{
					if (game->endGameAsk)
						quit = 1;
				}
				if (event.key.keysym.sym == SDLK_n)
				{
					if (game->endGameAsk)
						game->endGameAsk = false;
				}
				break;
				
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		frames++;
	};

	// freeing all surfaces
	delete game;
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
