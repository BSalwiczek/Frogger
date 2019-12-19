#pragma once
#include <string.h>


#include "Draw.h"
#include "Car.h"
#include "Base.h"
#include "Wood.h"
#include "Frog.h"
#include "Turtle.h"

#define CAR_ROWS 5
#define WOOD_ROWS 2
#define TURTLES_ROWS 3
#define BASES_COUNT 5

#define WATER_Y_START 186
#define WATER_Y_END 450

#define HEARTS_X 20
#define HEARTS_Y SCREEN_HEIGHT - 70

class Scene
{
public:
	bool error;

	SDL_Texture* carsTexture;
	SDL_Texture* baseTexture;
	SDL_Texture* woodTexture;
	SDL_Texture* turtleTexture;

	SDL_Surface* timeBar;
	SDL_Texture* timeBarTexture;

	Car*** cars;
	Wood*** woods;
	Turtle*** turtles;
	Base** bases;

	Scene(SDL_Renderer* renderer);
	~Scene();
	void createScene();
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

	SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
	bool detectEnemyCollisions(int frogX, int frogY, int frogWidth, int frogHeight); 
	bool detectBaseCollisions(int frogX, int frogY, int frogWidth, int frogHeight);
	bool detectWaterCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	int detectWoodCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	int detectTurtleCollision(int frogX, int frogY, int frogWidth, int frogHeight);
};

