#pragma once
#include "Frog.h"
#include "Entity.h"
#include <stdlib.h>

class LittleFrog: public Frog
{
	int woodWidth, woodX;
public:
	bool follow;

	LittleFrog(SDL_Texture* texture, int posX, int woodWidth, int posY);

	void checkIfTooFar();
	void moveAround(double fps);
};

