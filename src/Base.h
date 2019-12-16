#pragma once

#include "Draw.h"
#include "Entity.h"

class Base: public Entity
{
public:
	SDL_Texture* texture;
	bool visible;

	Base(SDL_Texture* texture, int posX, int posY);
	void show(Draw* draw);
};

