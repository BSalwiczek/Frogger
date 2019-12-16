#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
	this->worldTime = 0;
	this->fps = 0;
	this->level = 0;
	this->draw = new Draw(renderer);
	error = false;
	if (this->draw->error == true)
		this->error = true;

	this->frog = new Frog(renderer);
	if (this->frog->error == true)
		this->error = true;

	this->scene = new Scene(renderer);
	if (this->scene->error == true)
		this->error = true;
	this->scene->createScene();
	this->paused = false;
	this->over = false;
	this->endGameAsk = false;
}

Game::~Game()
{
	delete frog;
	delete draw;
	delete scene;
}

void Game::play()
{
	scene->drawScene(draw, fps, paused);
	scene->showLives(draw, frog);
	frog->showFrog(draw);

	if (!paused && !over)
	{
		if (scene->detectEnemyCollisions(frog->posX, frog->posY, frog->width, frog->height))
		{
			frog->die();
		}
		if (scene->detectBaseCollisions(frog->posX, frog->posY, frog->width, frog->height))
		{
			frog->goToStart();
		}

		int velocity = scene->detectWoodCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height);
		frog->external_velocity = velocity;
		frog->external_velocity_direction = right;

		if (scene->detectWaterCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height) && !frog->jumping)
		{
			frog->die();
		}

		frog->move(fps);
	}else if(!over){
		scene->showPaused(draw);
	}

	if(endGameAsk)
		scene->endGameAsk(draw);

	if (frog->lives == 0)
	{
		over = true;
		scene->showOver(draw);
	}
	
	
}