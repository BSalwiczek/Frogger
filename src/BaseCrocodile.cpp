#include "BaseCrocodile.h"


BaseCrocodile::BaseCrocodile(SDL_Texture* texture, short base)
{
	this->texture = texture;
	this->base = base;
	switch (base)
	{
	case 0:
		posX = 17;
		break;
	case 1:
		posX = 175;
		break;
	case 2:
		posX = 334;
		break;
	case 3:
		posX = 492;
		break;
	case 4:
		posX = 650;
		break;
	}
	posY = 138;
	animation_state = attact_start;
	last_animation_time = SDL_GetTicks();
}

void BaseCrocodile::show(Draw* draw)
{
	animate();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 18;
	if (animation_state == attact) {
		rect.x = 18;
		rect.w = 39;

	}
	rect.h = 42;
	draw->drawPartOfTexture(draw->renderer, texture, posX, posY, rect, 0, SDL_FLIP_NONE);
}

void BaseCrocodile::animate()
{
	if (SDL_GetTicks() - last_animation_time > 1000)
	{

		switch (animation_state)
		{
		case attact_start:
			animation_state = attact;
			break;
		case attact:
			animation_state = attact_end;
			break;
		case attact_end:
			break;
		}

		last_animation_time = SDL_GetTicks();
	}
}