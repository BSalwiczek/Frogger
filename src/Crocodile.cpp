#include "Crocodile.h"

Crocodile::Crocodile(SDL_Texture* texture, int posX, int posY, int velocity) : Entity(texture, posX, posY, velocity)
{
	direction = right;
	animation_state = jaws_closed;
	width = 87;
	height = 44;
}

void Crocodile::show(Draw* draw)
{
	SDL_Rect rect = {0,0,87,44};
	draw->drawPartOfTexture(draw->renderer, texture, (int)posX, (int)(posY - 8), rect, 0, SDL_FLIP_NONE);

	if (animation_state == jaws_open)
	{
		rect.x = 88;
		rect.w = 41;
		draw->drawPartOfTexture(draw->renderer, texture, (int)(posX + 87), (int)(posY - 8), rect, 0, SDL_FLIP_NONE);
	}
	else {
		rect.x = 131;
		rect.w = 39;
		draw->drawPartOfTexture(draw->renderer, texture, (int)(posX + 87), (int)(posY - 8), rect, 0, SDL_FLIP_NONE);
	}
}

void Crocodile::animate()
{
	if (SDL_GetTicks() - last_animation_time > 80000 / velocity)
	{
		if (animation_state == jaws_closed)
			animation_state = jaws_open;
		else
			animation_state = jaws_closed;
		last_animation_time = SDL_GetTicks();
	}
}