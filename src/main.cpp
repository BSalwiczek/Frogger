#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Game.h"

int main(int argc, char** argv) {
	int t1, t2, quit, frames, rc;
	double delta, fpsTimer, distance;
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;

	srand(time(NULL));

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

	SDL_ShowCursor(SDL_DISABLE);

	Game* game = new Game(renderer);

	t1 = SDL_GetTicks();

	fpsTimer = 0;
	quit = 0;
	frames = 0;

	while (!quit) {

		if (game->error)
		{
			delete game;
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
		game->delta = delta;
		t1 = t2;

		if(!game->paused && !game->over)
			game->worldTime += delta;

		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			game->fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		SDL_RenderClear(renderer);

		if (game->menu)
			game->scene->showMenu(game->draw, game->menuOption);
		else if (game->highscores)	
			game->scene->showHighScores(game->draw, game->names, game->highestScores, game->highestCount);
		else
			game->play();
		
		
		SDL_RenderPresent(renderer);

		if (game->over && game->savedToFile)
		{
			delete game;
			game = new Game(renderer);
		}

		// handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;

				if (event.key.keysym.sym == SDLK_p && !game->win)
					game->paused = !game->paused;
				else if (!game->paused) {
					game->frog->jump(event.key.keysym.sym);

					if(game->scene->littleFrog != NULL)
						if(game->scene->littleFrog->follow)
							game->scene->littleFrog->jump(event.key.keysym.sym);
				}

				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
				{
					if (game->menu)
						game->menuOption = !game->menuOption;
				}
				
				if (event.key.keysym.sym == SDLK_q && !game->win)
				{
					if (game->over)
						quit = 1;
					
					if (!game->endGameAsk)
						game->endGameAsk = true;

				}
				if (event.key.keysym.sym == SDLK_y && !game->win)
				{
					if (game->endGameAsk)
						quit = 1;
				}
				if (event.key.keysym.sym == SDLK_n && !game->win)
				{
					if (game->endGameAsk)
						game->endGameAsk = false;
				}

				if (event.key.keysym.sym == SDLK_r)
				{
					if (game->highscores)
					{
						game->highscores = false;
						game->menu = true;

					}
					if (game->over)
					{
						delete game;
						game = new Game(renderer);
					}
				}

				if (event.key.keysym.sym == SDLK_BACKSPACE)
				{
					if (game->getName)
						game->backspaceName();
				}

				if (event.key.keysym.sym == SDLK_RETURN)
				{
					if (game->getName)
						game->saveScore();

					if (game->menu)
					{
						if (game->menuOption == 0)
							game->menu = false;
						else {
							game->menu = false;
							game->highscores = true;
						}
					}
				}
				break;
			case SDL_TEXTINPUT:
				if (game->getName)
					game->writeName(event.text.text);
				break;
				
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		frames++;
	};

	delete game;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
};
