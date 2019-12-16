#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer)
{
	error = false;

	SDL_Surface* carsSprite = SDL_LoadBMP("src/bmp/cars.bmp");
	if (carsSprite == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	carsTexture = SDL_CreateTextureFromSurface(renderer, carsSprite);

	SDL_Surface* baseSprite = SDL_LoadBMP("src/bmp/base.bmp");
	if (baseSprite == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	baseTexture = SDL_CreateTextureFromSurface(renderer, baseSprite);

	SDL_Surface* woodSprite = SDL_LoadBMP("src/bmp/wood.bmp");
	if (woodSprite == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	woodTexture = SDL_CreateTextureFromSurface(renderer, woodSprite);
}

void Scene::createScene()
{
	cars = new Car**[CAR_ROWS];
	for (int i = 0; i < CAR_ROWS; i++)
	{
		cars[i] = new Car*[10];
		for (int j = 0; j < 10; j++)
		{
			cars[i][j] = new Car(carsTexture, i, 400*j, 730 - 55 * i, i%2==0? right: left);
		}
	}

	woods = new Wood **[WOOD_ROWS];
	for (int i = 0; i < WOOD_ROWS; i++)
	{
		woods[i] = new Wood * [10];
		for (int j = 0; j < 10; j++)
		{
			woods[i][j] = new Wood(woodTexture, 200 * j, 412 - 54 * i, i%3, 100/(i+1));
		}
	}

	bases = new Base*[BASES_COUNT];
	bases[0] = new Base(baseTexture, 19, 135);
	bases[1] = new Base(baseTexture, 177, 135);
	bases[2] = new Base(baseTexture, 336, 135);
	bases[3] = new Base(baseTexture, 494, 135);
	bases[4] = new Base(baseTexture, 652, 135);

	//car = new Car(carsTexture, 4,100,500, right);

}

void Scene::drawScene(Draw* draw, int fps, bool paused)
{
	for (int i = 0; i < CAR_ROWS; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if(!paused)
				cars[i][j]->move(fps);
			cars[i][j]->show(draw);
		}
	}

	for (int i = 0; i < WOOD_ROWS; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if(!paused)
				woods[i][j]->move(fps);
			woods[i][j]->show(draw);
		}
	}

	for (int i = 0; i < BASES_COUNT; i++)
	{
		bases[i]->show(draw);
	}
}

bool Scene::detectEnemyCollisions(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < CAR_ROWS; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (cars[i][j]->collision(frogX, frogY, frogWidth, frogHeight))
				return true;
		}
	}

	return false;
}

bool Scene::detectBaseCollisions(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < BASES_COUNT; i++)
	{
		if (bases[i]->collision(frogX, frogY, frogWidth, frogHeight))
		{
			bases[i]->visible = true;
			return true;
		}
	}
	return false;
}

int Scene::detectWoodCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	for (int i = 0; i < WOOD_ROWS; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (woods[i][j]->collision(frogX, frogY, frogWidth, frogHeight))
			{
				return woods[i][j]->velocity;
			}
		}
	}

	return 0;
}

bool Scene::detectWaterCollision(int frogX, int frogY, int frogWidth, int frogHeight)
{
	if (frogY + frogHeight / 2 > WATER_Y_START && frogY + frogHeight / 2 < WATER_Y_END)
	{
		for (int i = 0; i < WOOD_ROWS; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (woods[i][j]->centerCollision(frogX, frogY, frogWidth, frogHeight))
				{
					return false;
				}
			}
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

	draw->DrawString(draw->screen, draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h/2, text, draw->charset2, 32);
}

void Scene::showOver(Draw* draw)
{
	char text[128];
	sprintf(text, "GAME OVER");
	draw->DrawString(draw->screen, draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 16, text, draw->charset2, 32);
	sprintf(text, "Q-END GAME");
	draw->DrawString(draw->screen, draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 20, text, draw->charset2, 32);
	sprintf(text, "R-PLAY AGAIN");
	draw->DrawString(draw->screen, draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 + 56, text, draw->charset2, 32);
}

void Scene::endGameAsk(Draw* draw)
{
	char text[128];
	sprintf(text, "QUIT GAME? Y/N");
	draw->DrawString(draw->screen, draw->screen->w / 2 - strlen(text) * 32 / 2, draw->screen->h / 2 - 16, text, draw->charset2, 32);
}



Scene::~Scene()
{
	//for (int i = 0; i < CAR_ROWS - 1; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		delete cars[i][j];
	//	}
	//}
	//delete[] cars;
	//delete[] bases;
}