#include "Car.h"

Car::Car(SDL_Texture* texture, int car_type, int posX, int posY, int velocity, direction_t direction) : Entity(texture, posX, posY, velocity)
{
	carRect.y = 0;
	switch (car_type)
	{
	case 0:
		carRect.x = 0;
		carRect.w = 26;
		carRect.h = 34;
		break;
	case 1:
		carRect.x = 52;
		carRect.w = 50;
		carRect.h = 28;
		break;
	case 2:
		carRect.x = 102;
		carRect.w = 27;
		carRect.h = 28;
		break;
	case 3:
		carRect.x = 129;
		carRect.w = 30;
		carRect.h = 40;
		break;
	default:
		carRect.x = 159;
		carRect.w = 29;
		carRect.h = 40;
		break;
	}

	width = carRect.w;
	height = carRect.h;

	this->direction = direction;
}

void Car::show(Draw* draw)
{
	draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)posY, carRect, 0, SDL_FLIP_NONE);
}

void Car::animate()
{
	if (SDL_GetTicks() - last_animation_time > 20000 / velocity)
	{
		if (carRect.x == 0)
			carRect.x = 26;
		else if (carRect.x == 26)
			carRect.x = 0;
		else if (carRect.x == 159)
			carRect.x = 188;
		else if (carRect.x == 188)
			carRect.x = 159;
		last_animation_time = SDL_GetTicks();
	}
}