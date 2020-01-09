#pragma once

#include "Draw.h"
#include "Entity.h"

#define BASE_SIZE 48

class Base: public Entity
{
public:
	bool visible;
	Base(SDL_Texture* texture, int posX, int posY);
	void show(Draw* draw);
};

