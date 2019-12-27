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
	int bonus;
	int bonusX, bonusY;
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
	bool showBonus;

	char names[10][255];
	int highestScores[10];
	short highestCount;

	double fps, worldTime, bonusTime, beeTime, divingTime, baseCrocodileTime;
	double startedTime, endedTime;

	Draw* draw;
	Frog* frog;
	Scene* scene;

	Game(SDL_Renderer* renderer);
	~Game();
	void play();
	void showAll();
	void handleFrogDeath();
	void handleBonusesAndBases();
	void writeName(char *input);
	void backspaceName();
	void saveScore();
	void setExternalVelocity(Frog* frog);
	int getLevelsCount();

	bool isEmpty(FILE* file);
};
