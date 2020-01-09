#pragma once

#include "Draw.h"
#include "Entity.h"

#define TURTLE_WIDTH 48
#define TURTLE_HEIGHT 34

typedef enum {
	swim_start,
	swim_middle,
	swim_end,
	diving_start,
	diving_middle,
	diving_end
} turtle_animation;

class Turtle: public Entity
{
	int size;
public:
	turtle_animation animation_state;
	bool diving;
	Turtle(SDL_Texture* texture, int posX, int posY, int size, int velocity);
	void show(Draw* draw);
	void animate();
};

