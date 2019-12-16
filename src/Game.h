#pragma once

#include "Draw.h"
#include "Frog.h"
#include "Scene.h"

class Game
{
	int level;
public:
	bool paused;
	bool over;
	bool error;
	bool endGameAsk;
	double fps, worldTime;
	Draw* draw;
	Frog* frog;
	Scene* scene;

	Game(SDL_Renderer* renderer);
	~Game();
	void play();
};
