#pragma once

#include "Entity.h"
#include "Draw.h"

#define BEGIN_WIDTH 20
#define MIDDLE_WIDTH 51
#define END_WIDTH 72

class Wood: public Entity
{
	int size;
	double step;
public:
	int velocity;
	SDL_Texture* texture;
	Wood(SDL_Texture* texture, int posX, int posY, int size, int velocity);
	void show(Draw* draw);
	void move(int fps);
};

