#pragma once

#include "Draw.h"
#include "Entity.h"


class Car: public Entity
{
	SDL_Rect carRect;
public:
	Car(SDL_Texture* texture, int car_type, int posX, int posY, int velocity, direction_t direction);
	void show(Draw* draw);
	void animate();
};

