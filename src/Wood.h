#pragma once

#include "Entity.h"
#include "Draw.h"

#define WOOD_BEGIN_WIDTH 20
#define WOOD_MIDDLE_WIDTH 51
#define WOOD_END_WIDTH 72
#define WOOD_HEIGHT 34

class Wood: public Entity
{
	int size;
public:
	Wood(SDL_Texture* texture, int posX, int posY, int size, int velocity);
	void show(Draw* draw);
};

