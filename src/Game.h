#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../dirent/dirent.h"
#include "Draw.h"
#include "Frog.h"
#include "Scene.h"

class Game
{
	int levels, current_level, scores, bonus, bonusX, bonusY;
public:
	char name[255];
	short nameCurrentIndex, bases, menuOption;

	bool paused, over, error, win, endGameAsk, getName, menu, highscores, savedToFile, showBonus;
	double fps,delta, worldTime, bonusTime, beeTime, divingTime, baseCrocodileTime, startedTime, endedTime;

	char names[10][255];
	int highestScores[10];
	short highestCount;

	Draw* draw;
	Frog* frog;
	Scene* scene;

	Game(SDL_Renderer* renderer);
	~Game();
	void play();
	void showAll();
	void handleFrogDeath();
	void handleBonusesAndBases();
	void writeName(const char *input);
	void backspaceName();
	void saveScore();
	void setExternalVelocity(Frog* frog);

	int getLevelsCount();
	bool isEmpty(FILE* file);
};
