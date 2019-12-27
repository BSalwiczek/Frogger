#include "Crocodile.h"

Crocodile::Crocodile(SDL_Texture* texture, int posX, int posY, int velocity)
{
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;
	this->velocity = velocity;
	direction = right;
	animation_state = jaws_closed;
	width = 87;
	height = 44;
}


void Crocodile::show(Draw* draw)
{
	animate();
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 87;
	rect.h = 44;
	draw->drawPartOfTexture(draw->renderer, texture, posX, posY - 8, rect, 0, SDL_FLIP_NONE);

	if (animation_state == jaws_open)
	{
		rect.x = 88;
		rect.w = 41;
		draw->drawPartOfTexture(draw->renderer, texture, posX + 87, posY - 8, rect, 0, SDL_FLIP_NONE);
	}
	else {
		rect.x = 131;
		rect.w = 39;
		draw->drawPartOfTexture(draw->renderer, texture, posX + 87, posY - 8, rect, 0, SDL_FLIP_NONE);
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