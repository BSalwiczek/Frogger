#pragma once

#include "Entity.h"

typedef enum {
	attact_start,
	attact,
	attact_end
}base_crocodile_animation;

class BaseCrocodile: public Entity
{
	SDL_Texture* texture;
public:
	short base;
	base_crocodile_animation animation_state;

	BaseCrocodile(SDL_Texture* texture, short base);
	void show(Draw* draw);
	void animate();

};

