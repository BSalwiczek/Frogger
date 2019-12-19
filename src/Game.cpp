#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
	this->worldTime = 0;
	this->startedTime = 0;
	this->endedTime = 0;
	this->fps = 0;
	this->bases = 0;
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

	levels = 1;
	scores = 100;
	current_level = 1;
	getName = false;
	nameCurrentIndex = 0;
	name[0] = '\0';
	menu = true;
	win = false;
	highscores = false;
	menuOption = 0;

	//get highest scores
	FILE* file = fopen("scores.txt", "r");
	names[10][255];
	highestScores[10];
	highestCount = 0;
	while (fscanf(file, "%s , %d", names[highestCount], &highestScores[highestCount]) > 0)
	{
		highestCount++;
	}
}

Game::~Game()
{
	delete frog;
	delete draw;
	delete scene;
}

void Game::writeName(char* input)
{
	if (nameCurrentIndex < 253)
	{
		name[nameCurrentIndex] = input[0];
		name[nameCurrentIndex + 1] = '\0';
		nameCurrentIndex++;
	}
}

void Game::backspaceName()
{
	if (nameCurrentIndex > 0)
	{
		name[nameCurrentIndex-1] = '\0';
		nameCurrentIndex--;
	}
}

void Game::play()
{
	scene->showTimeBar(draw, (50.0-(worldTime-startedTime))/50.0);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT - 200;

	draw->drawPartOfTexture(draw->renderer, draw->background, 0, 100, rect, 0, SDL_FLIP_NONE);

	scene->drawScene(draw, fps, paused);

	scene->showScores(draw, scores);
	scene->showLives(draw, frog);
	frog->showFrog(draw);

	if (!paused && !over)
	{
		if (worldTime - startedTime > 50.0 && !frog->first_move)
		{
			endedTime = worldTime;
			frog->die();
		}
		if (scene->detectEnemyCollisions(frog->posX, frog->posY, frog->width, frog->height))
		{
			endedTime = worldTime;
			frog->die();
		}
		if (scene->detectBaseCollisions(frog->posX, frog->posY, frog->width, frog->height))
		{
			endedTime = worldTime;
			bases++;
			scores += 50 + 10 * (int)(worldTime - startedTime);
			frog->goToStart();
		}

		frog->external_velocity = 0;
		int velocity = scene->detectWoodCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height);
		if (velocity > 0)
		{
			frog->external_velocity = velocity;
			frog->external_velocity_direction = right;
		}

		velocity = scene->detectTurtleCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height);
		if (velocity > 0)
		{
			frog->external_velocity = velocity;
			frog->external_velocity_direction = left;
		}

		if (scene->detectWaterCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height) && !frog->jumping)
		{
			endedTime = worldTime;
			frog->die();
		}

		if (frog->posX < 0 || frog->posX > SCREEN_WIDTH - frog->width || frog->posY > SCREEN_HEIGHT - 100 || frog->posY < 150)
		{
			endedTime = worldTime;
			frog->die();
		}

		if (frog->lowestY > frog->posY & frog->jumping == false)
		{
			scores += 10;
			frog->lowestY = frog->posY;
		}

		if (bases == BASES_COUNT)
		{
			if (current_level == levels)
			{
				getName = true;
				win = true;
				frog->moveable = false;
				scene->showWin(draw, scores, name);
			}
			else {
				levels++;
			}
		}

		if (frog->first_move == true)
			startedTime = worldTime;



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

void Game::saveScore()
{
	if (nameCurrentIndex > 2)
	{
		FILE* file = fopen("scores.txt","a+");
		if (file == NULL)
			return;
		
		if (isEmpty(file))
		{
			fprintf(file, "%s , %i\n", name, scores);
			fprintf(file, "%s , %i\n",name, scores-10);
		}
		else
		{
			int worstScore = 100000000;
			int currentScore = 0;
			int lineWithWorstScore = -1, currentLine = 0;
			char someoneName[255];
			while (fscanf(file, "%s , %d", someoneName, &currentScore) > 0)
			{
				if (currentScore < worstScore) {
					worstScore = currentScore;
					lineWithWorstScore = currentLine;
				}
				currentLine++;
			}
			if (lineWithWorstScore == -1)
				return;

			if (currentLine < 10)
			{
				fprintf(file, "%s , %i\n", name, scores);
				fclose(file);

			}
			else {
				currentLine = 0;
				char ch;
				rewind(file);

				FILE* file2 = fopen("temp.txt", "w");

				bool lineWrote = false;
				while ((ch = fgetc(file)) != EOF)
				{
					if (currentLine == lineWithWorstScore)
					{
						if (!lineWrote)
						{
							fprintf(file2, "%s , %i\n", name, scores);
							lineWrote = true;
						}
						
					}
					else{
						fprintf(file2, "%c", ch);
					}
					
					if (ch == '\n')
						currentLine++;
				}

				fclose(file2);
				fclose(file);
				remove("scores.txt");
				rename("temp.txt", "scores.txt");
			}
		}

	}
}

bool Game::isEmpty(FILE* file) {
	long savedOffset = ftell(file);
	fseek(file, 0, SEEK_END);

	if (ftell(file) == 0) {
		return true;
	}

	fseek(file, savedOffset, SEEK_SET);
	return false;
}