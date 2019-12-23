#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Draw.h"
#include "Car.h"
#include "Base.h"
#include "Wood.h"
#include "Frog.h"
#include "Turtle.h"
#include "LittleFrog.h"

#define BASES_COUNT 5

#define WATER_Y_START 186
#define WATER_Y_END 450

#define HEARTS_X 20
#define HEARTS_Y SCREEN_HEIGHT - 70

class Scene
{
	int woods_amount, turtles_amount, cars_amount;
public:
	bool error;
	float time_for_level;

	SDL_Texture* carsTexture;
	SDL_Texture* baseTexture;
	SDL_Texture* woodTexture; 
	SDL_Texture* littleFrogTexture;
	SDL_Texture* frogTexture;
	SDL_Texture* turtleTexture;

	SDL_Surface* timeBar;
	SDL_Texture* timeBarTexture;

	Car** cars;
	Wood** woods;
	Turtle** turtles;
	Base** bases;
	LittleFrog* littleFrog;

	Scene(SDL_Renderer* renderer);
	~Scene();
	void createScene(int level);
	void resetScene();
	void drawScene(Draw* draw, int fps, bool paused);
	void showLives(Draw* draw, Frog* frog);
	void showPaused(Draw* draw); 
	void showOver(Draw* draw);
	void showWin(Draw* draw, int scores, char name[]);
	void showScores(Draw* draw, int scores);
	void showTimeBar(Draw* draw, double len);
	void endGameAsk(Draw* draw);
	void showMenu(Draw* draw, int option);
	void showHighScores(Draw* draw, char names[10][255], int highestScores[10], short highestCount);
	void show200(Draw* draw, int x, int y);

	SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
	bool detectEnemyCollisions(int frogX, int frogY, int frogWidth, int frogHeight); 
	bool detectBaseCollisions(int frogX, int frogY, int frogWidth, int frogHeight);
	bool detectWaterCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	int detectWoodCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	int detectTurtleCollision(int frogX, int frogY, int frogWidth, int frogHeight);
};

