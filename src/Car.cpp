#include "Car.h"


Car::Car(SDL_Texture* carsTexture, int car_type, int posX, int posY, direction_t direction)
{
	this->carsTexture = carsTexture;
	this->posX = posX;
	this->posY = posY;
	this->carRect.y = 0;
	this->step = 0;
	switch (car_type)
	{
	case 0:
		this->carRect.x = 0;
		this->carRect.w = 26;
		this->carRect.h = 32;
		break;
	case 1:
		this->carRect.x = 26;
		this->carRect.w = 50;
		this->carRect.h = 28;
		break;
	case 2:
		this->carRect.x = 76;
		this->carRect.w = 27;
		this->carRect.h = 28;
		break;
	case 3:
		this->carRect.x = 103;
		this->carRect.w = 30;
		this->carRect.h = 40;
		break;
	default:
		this->carRect.x = 133;
		this->carRect.w = 29;
		this->carRect.h = 40;
		break;
	}

	this->width = carRect.w;
	this->height = carRect.h;

	this->direction = direction;
	this->velocity = 40;
}

void Car::show(Draw* draw)
{
	draw->drawPartOfTexture(draw->renderer, this->carsTexture, this->posX, this->posY, this->carRect, 0, SDL_FLIP_NONE);
}

void Car::move(int fps)
{
	if(fps>0)
		this->step = velocity * (1/(double)fps) + this->step;
	if (this->step >= 1)
	{
		if (this->direction == left)
			this->posX -= 1;
		if (this->direction == right)
			this->posX += 1;
		if (this->posX > SCREEN_WIDTH * 2 - this->carRect.w)
			this->posX = -this->carRect.w;
		if (this->posX < -SCREEN_WIDTH + this->carRect.w)
			this->posX = SCREEN_WIDTH + this->carRect.w;

		this->step = 0;
	}

}