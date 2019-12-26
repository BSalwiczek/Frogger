#include "Bee.h"

Bee::Bee(SDL_Texture* texture, short base)
{
	switch (base)
	{
	case 0:
		posX = 19;
		break;
	case 1:
		posX = 177;
		break;
	case 2:
		posX = 336;
		break;
	case 3:
		posX = 494;
		break;
	case 4:
		posX = 652;
		break;
	}
	posY = 138;
	this->texture = texture;
	this->base = base;
}

void Bee::show(Draw* draw)
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 49;
	rect.h = 39;
	draw->drawPartOfTexture(draw->renderer, texture, posX, posY, rect, 0, SDL_FLIP_NONE);
}
