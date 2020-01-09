#pragma once

#include "Entity.h"

#define BASE_CROCODILE_WIDTH 18
#define BASE_CROCODILE_HEIGHT 42

typedef enum {
	attact_start,
	attact,
	attact_end
}base_crocodile_animation;

class BaseCrocodile: public Entity
{
public:
	short base;
	base_crocodile_animation animation_state;

	BaseCrocodile(SDL_Texture* texture, short base);
	void show(Draw* draw);
	void animate();
};

