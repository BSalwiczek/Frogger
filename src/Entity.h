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
	direction_t direction;
	int velocity; //pixels every second
	int posX, posY, width, height;
	int last_animation_time;
	double step;

	bool collision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool centerCollision(int frogX, int frogY, int frogWidth, int frogHeight);
	bool beetwen(int x, int up, int down);
	void move(int fps);
	void show(Draw* draw);
	Entity();
};

