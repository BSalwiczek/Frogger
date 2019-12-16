#pragma once

#include <math.h>
#include "Draw.h"

typedef enum {
	left,
	right,
	up,
	down
} direction_t;

class Entity
{
public:
	direction_t direction;
	int velocity; //pixels every second
	int posX, posY, width, height;

	bool collision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool centerCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool beetwen(int x, int up, int down);
	void show(Draw* draw);
	Entity();
};

