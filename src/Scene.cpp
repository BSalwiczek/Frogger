#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer)
{
	error = false;
	woods_amount = 0;
	cars_amount = 0;
	turtles_amount = 0;
	time_for_level = 100.0;
	bee_chance = 0;
	little_frog_chance = 0;
	base_crocodile_chance = 0;

	carsTexture = loadTexture(renderer, "src/bmp/cars.bmp");
	baseTexture = loadTexture(renderer, "src/bmp/base.bmp");
	woodTexture = loadTexture(renderer, "src/bmp/wood.bmp");
	turtleTexture = loadTexture(renderer, "src/bmp/turtle.bmp");
	littleFrogTexture = loadTexture(renderer, "src/bmp/littlefrog.bmp");
	frogTexture = loadTexture(renderer, "src/bmp/frog.bmp");
	beeTexture = loadTexture(renderer, "src/bmp/bee.bmp");
	baseCrocodileTexture = loadTexture(renderer, "src/bmp/baseCrocodile.bmp");
	crocodileTexture = loadTexture(renderer, "src/bmp/crocodile.bmp");

	timeBar = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_FillRect(timeBar, NULL, SDL_MapRGBA(timeBar->format, 0, 0, 0, 0));

	timeBarTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
}

SDL_Texture* Scene::loadTexture(SDL_Renderer* renderer, char* path)
{
	SDL_Surface* surface = SDL_LoadBMP(path);
	if (surface == NULL)
	{
		printf("SDL_LoadBMP(%s) error: %s\n",path, SDL_GetError());
		error = true;
		return false;
	}
	return SDL_CreateTextureFromSurface(renderer, surface);
}

void Scene::createScene(int level)
{
	char text[10];
	sprintf(text, "etap%i.txt",level);
	FILE* file = fopen(text,"r");
	
	char buffer[100];
	char name;
	int amount, time = 0, chance = 0;

	fgets(buffer, sizeof buffer / sizeof buffer[0], file);
	if (sscanf(buffer, "Time: %i", &time) > 0)
	{
		time_for_level = time;
	}

	fgets(buffer, sizeof buffer / sizeof buffer[0], file);
	if (sscanf(buffer, "Bee chance: %i", &chance) > 0)
	{
		bee_chance = chance;
	}

	fgets(buffer, sizeof buffer / sizeof buffer[0], file);
	if (sscanf(buffer, "Little frog chance: %i", &chance) > 0)
	{
		little_frog_chance = chance;
	}

	fgets(buffer, sizeof buffer / sizeof buffer[0], file);
	if (sscanf(buffer, "Base crocodile chance: %i", &chance) > 0)
	{
		base_crocodile_chance = chance;
	}

	for (int i = 0; i < 4; i++)
	{
		fgets(buffer, sizeof buffer / sizeof buffer[0], file);
		if (sscanf(buffer, "%c %i", &name, &amount) > 0)
		{
			printf("%c %i \n", name, amount);
			if (name == 'W') {
				woods_amount = amount;
				woods = new Wood * [amount];
			}
			if (name == 'T') {
				turtles_amount = amount;
				turtles = new Turtle * [amount];
			}
			if (name == 'C') {
				cars_amount = amount;
				cars = new Car * [amount];
			}
			if (name == 'K') {
				crocodiles_amount = amount;
				crocodiles = new Crocodile * [amount];
			}
		}
	}
	

	int rows[10];
	int woods_index = 0;
	int cars_index = 0;
	int turtles_index = 0;
	int crocodiles_index = 0;

	for(int i=0;i<10;i++)
	{
		int y;
		fgets(buffer, sizeof buffer / sizeof buffer[0], file);
		if (sscanf(buffer, "%i %i", &rows[i], &y) > 0)
		{
			printf("%i %i \n", rows[i], y);
			while (feof(file) == 0)
			{
				int x = 0, velocity = 0, size = 0, car_type = 0, direction = 0;
				char name = ' ';
				fgets(buffer, sizeof buffer / sizeof buffer[0], file);
				if (sscanf(buffer, "%c %i %i %i", &name, &x, &velocity, &size) > 0 && (name == 'W' || name == 'T' || name == 'K'))
				{
					printf("%c %i %i %i \n", name, x, velocity, size);
					if (name == 'W')
					{
						woods[woods_index] = new Wood(woodTexture, x, y, size, velocity);
						woods_index++;
					}
					else if (name == 'T')
					{
						turtles[turtles_index] = new Turtle(turtleTexture, x, y, size, velocity);
						turtles_index++;
					}
					else if (name == 'K')
					{
						crocodiles[crocodiles_index] = new Crocodile(crocodileTexture, x, y, velocity);
						crocodiles_index++;
					}
					
				}
				else if (sscanf(buffer, "%c %i %i %i %i", &name, &x, &car_type, &velocity, &direction) > 0 && name == 'C')
				{
					printf("%c %i %i %i %i \n", name, x, car_type, velocity, direction);

					cars[cars_index] = new Car(carsTexture,car_type, x, y, velocity, direction == 0 ? left : right);
					cars_index++;
				}

				if (velocity == 0)
					break;
			}
		}
	}

	fclose(file);

	printf("Cars index %i \n", cars_index);
	printf("Wood index %i \n", woods_index);
	printf("Turtles index %i \n", turtles_index);


	bases = new Base*[BASES_COUNT];
	bases[0] = new Base(baseTexture, 19, 135);
	bases[1] = new Base(baseTexture, 177, 135);
	bases[2] = new Base(baseTexture, 336, 135);
	bases[3] = new Base(baseTexture, 494, 135);
	bases[4] = new Base(baseTexture, 652, 135);

	littleFrog = NULL;
	bee = NULL;
	baseCrocodile = NULL;

	//createLittleFrog();
	//createBee();
	//createBaseCrocodile();
}

void Scene::createLittleFrog()
{
	if (littleFrog == NULL)
	{
		int littleFrogXPos = 0;
		for (int i = 0; i < woods_amount; i++)
		{
			if (woods[i]->posY == 358) {
				littleFrogXPos = woods[i]->posX + woods[i]->width/2 - 50;
				break;
			}
		}
		littleFrog = new LittleFrog(littleFrogTexture, littleFrogXPos, 358);
	}
}

bool Scene::createBaseCrocodile()
{
	bool created = false;
	if (baseCrocodile == NULL)
	{
		for (int i = 0; i < BASES_COUNT; i++)
		{
			if (bases[i]->visible == false && rand() % 100 < 20) {
				if (bee != NULL)
					if (bee->base == i)
						continue;
				baseCrocodile = new BaseCrocodile(baseCrocodileTexture, i);
				created = true;
				break;
			}

		}
	}
	return created;
}


bool Scene::createBee()
{
	bool created = false;
	if (bee == NULL)
	{
		for (int i = 0; i < BASES_COUNT; i++)
		{
			if (bases[i]->visible == false && rand()%100 < 20) {
				if (baseCrocodile != NULL)
					if (baseCrocodile->base == i)
						continue;
				bee = new Bee(beeTexture, i);
				created = true;
				break;
			}

		}
	}
	return created;
}

void Scene::resetScene()
{
	for (int i = 0; i < cars_amount; i++)
		delete cars[i];

	for (int i = 0; i < woods_amount; i++)
		delete woods[i];

	for (int i = 0; i < turtles_amount; i++)
		delete turtles[i];

	for (int i = 0; i < crocodiles_amount; i++)
		delete crocodiles[i];

	for (int i = 0; i < BASES_COUNT; i++)
		delete bases[i];

	if(cars_amount>0) delete[] cars;
	//if(turtles_amount>0) delete[] turtles;
	//if (crocodiles_amount > 0) delete[] crocodiles;

	delete[] bases;

	woods_amount = 0;
	cars_amount = 0;
	turtles_amount = 0;
	crocodiles_amount = 0;
}

void Scene::drawScene(Draw* draw, int fps, bool paused)
{
	for (int i = 0; i < cars_amount; i++)
	{
		if(!paused)
			cars[i]->move(fps);
		cars[i]->show(draw);
	}

	for (int i = 0; i < woods_amount; i++)
	{
		if(!paused)
			woods[i]->move(fps);
		woods[i]->show(draw);
	}

	for (int i = 0; i < turtles_amount; i++)
	{
		if (!paused)
			turtles[i]->move(fps);
		turtles[i]->show(draw);
	}

	for (int i = 0; i < crocodiles_amount; i++)
	{
		if (!paused)
			crocodiles[i]->move(fps);
		crocodiles[i]->show(draw);
	}

	for (int i = 0; i < BASES_COUNT; i++)
	{
		bases[i]->show(draw);
	}
}

bool Scene::detectEnemyCollisions(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < cars_amount; i++)
	{
		if (cars[i]->collision(frogX, frogY, frogWidth, frogHeight))
			return true;
	}

	return false;
}

int Scene::detectBaseCollisions(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < BASES_COUNT; i++)
	{
		if (bases[i]->collision(frogX, frogY, frogWidth, frogHeight))
		{
			if (bases[i]->visible == true)
				return -2;
			if (baseCrocodile != NULL) {
				if (!(i == baseCrocodile->base && baseCrocodile->animation_state == attact))
					bases[i]->visible = true;
			}else
				bases[i]->visible = true;

			return i;
		}
	}
	return -1;
}

int Scene::detectCrocodileCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < crocodiles_amount; i++)
	{
		if (crocodiles[i]->collision(frogX, frogY, frogWidth, frogHeight))
			return crocodiles[i]->velocity;
	}
	return 0;
}

int Scene::detectWoodCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < woods_amount; i++)
	{
		if (woods[i]->collision(frogX, frogY, frogWidth, frogHeight))
			return woods[i]->velocity;
	}
	return 0;
}

int Scene::detectTurtleCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < turtles_amount; i++)
	{
		if (turtles[i]->collision(frogX, frogY, frogWidth, frogHeight) && turtles[i]->animation_state != diving_middle)
			return turtles[i]->velocity;
	}
	return 0;
}

void Scene::randomTurtlesDive()
{
	if (turtles_amount > 0)
	{
		int turtle_index = rand() % turtles_amount;
		turtles[turtle_index]->diving = true;
	}
}

bool Scene::detectWaterCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	if (frogY + frogHeight / 2 > WATER_Y_START && frogY + frogHeight / 2 < WATER_Y_END)
	{
		for (int i = 0; i < woods_amount; i++)
		{
			if (woods[i]->centerCollision(frogX, frogY, frogWidth, frogHeight))
				return false;
		}
		for (int i = 0; i < turtles_amount; i++)
		{
			if (turtles[i]->centerCollision(frogX, frogY, frogWidth, frogHeight) && turtles[i]->animation_state != diving_middle)
				return false;
		}
		for (int i = 0; i < crocodiles_amount; i++)
		{
			if (crocodiles[i]->centerCollision(frogX, frogY, frogWidth, frogHeight))
				return false;
		}
		return true;
	}
	return false;
}


void Scene::showLives(Draw* draw, Frog* frog)
{
	SDL_Rect SrcR;
	SrcR.y = 0;
	SrcR.x = 83;
	SrcR.w = 40;
	SrcR.h = 33;
	for (int i = 0; i < frog->lives; i++)
	{
		draw->drawPartOfTexture(draw->renderer, frog->frogTexture, HEARTS_X + (SrcR.w+5)*i, HEARTS_Y, SrcR, 0, SDL_FLIP_NONE);
	}
}

void Scene::showPaused(Draw* draw)
{
	char text[128];
	sprintf(text, "PAUSED [p]");

	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h/2, text, draw->charset2, 32);
}

void Scene::showOver(Draw* draw)
{
	char text[128];
	sprintf(text, "GAME OVER");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 16, text, draw->charset2, 32);
	sprintf(text, "Q-END GAME");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 20, text, draw->charset2, 32);
	sprintf(text, "R-PLAY AGAIN");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 56, text, draw->charset2, 32);
}

void Scene::endGameAsk(Draw* draw)
{
	char text[128];
	sprintf(text, "QUIT GAME? Y/N");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 16, text, draw->charset2, 32);
}


void Scene::showWin(Draw* draw, int scores, char name[])
{
	draw->DrawFullScreenTexture();
	 
	char text[128];
	sprintf(text, "You won!");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 100, text, draw->charset2, 32);
	sprintf(text, "Score: %i", scores);
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 48, text, draw->charset2, 32);
	sprintf(text, "Enter your name: ");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 16, text, draw->charset2, 32);
	if (name[0] != '\0')
	{
		sprintf(text, "%s", name);
		draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 64, text, draw->charset2, 32);
	}
	
}

void Scene::showTimeBar(Draw* draw, double len)
{
	SDL_FillRect(timeBar, NULL, SDL_MapRGBA(timeBar->format, 0, 0, 0, 0));

	int length = (int)(250 * len);

	if(len > 0.25)
		draw->DrawRectangle(timeBar, SCREEN_WIDTH - 400 + 250 - length, SCREEN_HEIGHT - 60 , length, 25, draw->black, draw->green);
	else
		draw->DrawRectangle(timeBar, SCREEN_WIDTH - 400 + 250 - length, SCREEN_HEIGHT - 60, length, 25, draw->black, draw->red);

	SDL_UpdateTexture(timeBarTexture, NULL, timeBar->pixels, timeBar->pitch);
	SDL_RenderCopy(draw->renderer, timeBarTexture, NULL, NULL);

	char text[128];
	sprintf(text, "TIME");
	draw->DrawString(draw->screen->w - 140, draw->screen->h - 63 , text, draw->charset2, 32);
}

void Scene::showScores(Draw* draw, int scores)
{
	char text[128];
	sprintf(text, "SCORES: %i",scores);
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, 40, text, draw->charset2, 32);
}

void Scene::showMenu(Draw* draw, int option)
{
	draw->DrawFullScreenTexture();

	char text[128];
	sprintf(text, "-- Menu --");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 100, text, draw->charset2, 32);
	if(option == 0)
		sprintf(text, ">Play ");
	else
		sprintf(text, "Play ");
	draw->DrawString(draw->screen->w / 2 - 11 * 32 / 2, draw->screen->h / 2 - 32, text, draw->charset2, 32);
	if(option == 1)
		sprintf(text, ">High scores");
	else
		sprintf(text, "High scores");
		draw->DrawString(draw->screen->w / 2 - 11 * 32 / 2, draw->screen->h / 2 + 16, text, draw->charset2, 32);

}

void Scene::showHighScores(Draw* draw, char names[10][255], int highestScores[10], short highestCount)
{
	draw->DrawFullScreenTexture();

	char text[128];
	sprintf(text, "return [r]");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, 25, text, draw->charset2, 32);
	sprintf(text, "-- Highest Scores --");
	draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, 100, text, draw->charset2, 32);

	for (int i = 0; i < 10; i++)
	{
		sprintf(text, "%s %i", names[i], highestScores[i]);
		draw->DrawString(draw->screen->w / 2 - strlen(text) * 32 / 2, 180 + i*55, text, draw->charset2, 32);
	}

}

void Scene::showBonus(Draw* draw,int x, int y, int bonus)
{
	char text[4];
	if(bonus == 200)
		sprintf(text, "200");
	if (bonus == 400)
		sprintf(text, "400");
	draw->DrawString(x, y, text, draw->charset2, 32);

}


Scene::~Scene()
{
	SDL_DestroyTexture(carsTexture);
	SDL_DestroyTexture(baseTexture);
	SDL_DestroyTexture(woodTexture);
	SDL_DestroyTexture(turtleTexture);
	SDL_FreeSurface(timeBar);
	SDL_DestroyTexture(timeBarTexture);

	resetScene();
}