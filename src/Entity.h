#pragma once

#include <math.h>
#include "Draw.h"

typedef enum {
	left,
	right,
	up,
	down,
	none
} direction_t;

class Entity
{
public:
	SDL_Texture* texture;

	direction_t direction;
	int velocity, last_animation_time, width, height;
	float posX, posY;

	bool collision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool centerCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool beetwen(int x, int up, int down);
	void move(double delta);
	Entity(SDL_Texture* texture, double posX, double posY, int velocity);
};

