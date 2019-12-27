#pragma once

#include "Entity.h"

typedef enum {
	jaws_open,
	jaws_closed
}crocodile_animation;

class Crocodile: public Entity
{
public:
	SDL_Texture* texture;
	crocodile_animation animation_state;
	Crocodile(SDL_Texture* texture, int posX, int posY, int velocity);
	void show(Draw* draw);
	void animate();
};

