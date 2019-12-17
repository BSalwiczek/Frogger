#pragma once

#include "Draw.h"
#include "Entity.h"

#define TURTLE_WIDTH 48
#define TURTLE_HEIGHT 34

typedef enum {
	swim_start,
	swim_middle,
	swim_end
} turtle_animation;

class Turtle: public Entity
{
	int size;
	double step;
	int last_animation_time;
	turtle_animation animation_state;
public:
	int velocity;
	SDL_Texture* texture;
	Turtle(SDL_Texture* texture, int posX, int posY, int size, int velocity);
	void show(Draw* draw);
	void move(int fps);
	void setAnimation();
};

