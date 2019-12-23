#pragma once
#include "Frog.h"
#include "Entity.h"

class LittleFrog: public Frog
{
public:
	LittleFrog(SDL_Texture* texture, int posX, int posY);
	bool collision(int frogX, int frogY, int frogWidth, int frogHeight);

	void checkIfTooFar();
	bool follow;
};

