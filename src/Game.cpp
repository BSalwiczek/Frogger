#include "Game.h"

Game::Game(SDL_Renderer* renderer)
{
	worldTime = 0;
	bonusTime = 0;
	startedTime = 0;
	endedTime = 0;
	fps = 0;
	bases = 0;
	bonusX = 0;
	bonusY = 0;
	bonus = 0;
	beeTime = 0;
	divingTime = 0;
	baseCrocodileTime = 0;
	draw = new Draw(renderer);
	error = false;
	if (draw->error == true)
		error = true;

	scene = new Scene(renderer);
	if (scene->error == true)
		error = true;

	frog = new Frog(scene->frogTexture);
	if (frog->error == true)
		error = true;


	levels = getLevelsCount();
	current_level = 2;
	printf("%i \n", levels);

	scene->createScene(current_level);

	showBonus = false;
	menu = true;
	paused = false;
	over = false;
	endGameAsk = false;
	getName = false;
	savedToFile = false;
	win = false;
	highscores = false;

	scores = 300;
	nameCurrentIndex = 0;
	name[0] = '\0';
	
	menuOption = 0;

	//get highest scores
	FILE* file = fopen("scores.txt", "r");
	names[10][255];
	highestScores[10];
	highestCount = 0;
	while (fscanf(file, "%s , %d", names[highestCount], &highestScores[highestCount]) > 0)
	{
		highestCount++;
		if (highestCount > 9)
			break;
	}
	fclose(file);
}

int Game::getLevelsCount() 
{
	DIR* d;
	struct dirent* dir;
	int files = 0;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (!strncmp("etap", dir->d_name,4))
			{
				printf("%s \n", dir->d_name);
				files++;
			}
		}
		closedir(d);
	}
	return files;
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
	showAll();

	if (!paused && !over)
	{
		if (worldTime - startedTime > scene->time_for_level && !frog->first_move)
			handleFrogDeath();

		if (scene->detectEnemyCollisions(frog->posX, frog->posY, frog->width, frog->height))
			handleFrogDeath();

		if (scene->detectWaterCollision(this->frog->posX, this->frog->posY, this->frog->width, this->frog->height) && !frog->jumping)
			handleFrogDeath();

		if (frog->posX < 0 || frog->posX > SCREEN_WIDTH - frog->width || frog->posY > SCREEN_HEIGHT - 100 || frog->posY < 150)
			handleFrogDeath();

		handleBonusesAndBases();
		setExternalVelocity(frog);

		if (worldTime - divingTime > 1)
		{
			if (rand() % 100 > 80)
			{
				scene->randomTurtlesDive();
				divingTime = worldTime;
			}
			
		}

		if (frog->lowestY > frog->posY & frog->jumping == false)
		{
			scores += 10;
			frog->lowestY = frog->posY;
		}

		if (bases == BASES_COUNT)
		{
			if (current_level > levels)
			{
				getName = true;
				win = true;
				frog->moveable = false;
				scene->showWin(draw, scores, name);
			}
			else {
				bases = 0;
				frog->lives = MAX_LIVES;
				current_level++;
				scene->resetScene();
				scene->createScene(current_level);
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

void Game::handleFrogDeath()
{
	endedTime = worldTime;
	frog->die();
	if (scene->littleFrog != NULL)
		scene->littleFrog = NULL;
}


void Game::showAll()
{
	scene->showTimeBar(draw, (scene->time_for_level - (worldTime - startedTime)) / scene->time_for_level);

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

	if (scene->littleFrog != NULL)
		scene->littleFrog->showFrog(draw);
	if (scene->bee != NULL)
		scene->bee->show(draw);
	if (scene->baseCrocodile != NULL)
		scene->baseCrocodile->show(draw);
}

void Game::handleBonusesAndBases()
{
	int base = scene->detectBaseCollisions(frog->posX, frog->posY, frog->width, frog->height);
	if (base != -1)
	{
		if (scene->baseCrocodile != NULL && scene->baseCrocodile->base == base && scene->baseCrocodile->animation_state == attact) {
			handleFrogDeath();
		}
		else
		{
			bonus = 0;
			endedTime = worldTime;
			bases++;
			if (scene->littleFrog != NULL)
			{
				if (scene->littleFrog->follow) {
					bonus += 200;
					showBonus = true;
				}
				scene->littleFrog = NULL;
			}
			if (scene->bee != NULL)
			{
				if (scene->bee->base == base) {
					bonus += 200;
					showBonus = true;
				}
				scene->bee = NULL;
			}
			bonusX = frog->posX - 20;
			bonusY = frog->posY - 40;
			scores += bonus;
			scores += 50 + 10 * (int)(worldTime - startedTime);
			frog->goToStart();
		}
		
	}
	if (base == -2) //wczesniej zajeta
		handleFrogDeath();

	if (worldTime - endedTime < 5 && showBonus)
		scene->showBonus(draw, bonusX, bonusY, bonus);
	else
		showBonus = false;

	if (scene->littleFrog != NULL)
	{
		setExternalVelocity(scene->littleFrog);
		if (scene->littleFrog->collision(frog->posX, frog->posY, frog->width, frog->height))
		{
			scene->littleFrog->follow = true;
			scene->littleFrog->posX = frog->posX;
			scene->littleFrog->posY = frog->posY + 7;
		}

		scene->littleFrog->move(fps);
		scene->littleFrog->checkIfTooFar();
	}

	if (worldTime - bonusTime > 1)
	{
		if (rand() % 100 < scene->bee_chance)
		{
			if (scene->createBee())
			{
				beeTime = worldTime;
			};
		}
		if (rand() % 100 < scene->little_frog_chance)
		{
			scene->createLittleFrog();
		}
		if (rand() % 100 < scene->base_crocodile_chance)
		{
			if (scene->createBaseCrocodile())
			{
				baseCrocodileTime = worldTime;
			}
		}
		bonusTime = worldTime;
	}
	
	if (worldTime - baseCrocodileTime > 5)
	{
		scene->baseCrocodile = NULL;
	}

	if (worldTime - beeTime > 5)
	{
		scene->bee = NULL;
	}
}


void Game::setExternalVelocity(Frog* frog)
{
	frog->external_velocity = 0;
	int velocity = scene->detectWoodCollision(frog->posX, frog->posY, frog->width, frog->height);
	if (velocity > 0)
	{
		frog->external_velocity = velocity;
		frog->external_velocity_direction = right;
	}

	velocity = scene->detectTurtleCollision(frog->posX, frog->posY, frog->width, frog->height);
	if (velocity > 0)
	{
		frog->external_velocity = velocity;
		frog->external_velocity_direction = left;
	}

	velocity = scene->detectCrocodileCollision(frog->posX, frog->posY, frog->width, frog->height);
	if (velocity > 0)
	{
		frog->external_velocity = velocity;
		frog->external_velocity_direction = right;
	}
}

void Game::saveScore()
{
	if (nameCurrentIndex > 2 && !savedToFile)
	{
		FILE* file = fopen("scores.txt","a+");
		if (file == NULL)
			return;
		
		if (isEmpty(file))
		{
			fprintf(file, "%s , %i\n", name, scores);
		}
		else
		{
			int worstScore = 100000000;
			int currentScore = 0;
			int lineWithWorstScore = -1, currentLine = 0;
			char someoneName[255];
			while (fscanf(file, "%s , %d", someoneName, &currentScore) > 0)
			{
				if (currentScore <= worstScore) {
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
			else if(worstScore<=scores) {
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
		fclose(file);
		savedToFile = true;
		over = true;
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