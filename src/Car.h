#pragma once

#include "Draw.h"
#include "Entity.h"


class Car: public Entity
{
	SDL_Texture* carsTexture;
	SDL_Rect carRect;
	int velocity;
	double step;
public:
	bool error;

	Car(SDL_Texture* carsTexture, int car_type, int posX, int posY, int velocity, direction_t direction);
	void show(Draw* draw);
	void move(int fps);

};

