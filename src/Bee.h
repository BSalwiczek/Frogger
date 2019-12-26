#pragma once

#include "Entity.h"

class Bee: public Entity
{
	SDL_Texture* texture;
public:
	short base;

	Bee(SDL_Texture* texture, short base);
	void show(Draw* draw);
};

