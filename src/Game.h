#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../dirent/dirent.h"
#include "Draw.h"
#include "Frog.h"
#include "Scene.h"

class Game
{
	int levels;
	int current_level;
	int scores;
	int x200, y200;
public:
	char name[255];
	short nameCurrentIndex;
	short bases;
	short menuOption;

	bool paused;
	bool over;
	bool error;
	bool win;
	bool endGameAsk;
	bool getName;
	bool menu;
	bool highscores;
	bool savedToFile;
	bool show200;

	char names[10][255];
	int highestScores[10];
	short highestCount;

	double fps, worldTime;
	double startedTime, endedTime;

	Draw* draw;
	Frog* frog;
	Scene* scene;

	Game(SDL_Renderer* renderer);
	~Game();
	void play();
	void writeName(char *input);
	void backspaceName();
	void saveScore();
	void setExternalVelocity(Frog* frog);
	int getLevelsCount();

	bool isEmpty(FILE* file);
};
